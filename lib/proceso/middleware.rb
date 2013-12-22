require 'rack'

module Proceso
  class Middleware

    SUBSCRIPTION = 'proceso.usage'

    def self.report
      subscribe do |name, start, finish, id, payload|
        puts
        puts "******* PROCESO INFORMATION *******"
        mem_used    = (payload[:mem_used].to_f / 1024.0).round(1)
        cpu_used    = payload[:cpu_used].to_f.round(1)
        path        = payload[:request].path_info
        resp_time   = payload[:resp_time]
        puts "MEM: #{mem_used}KB CPU: #{cpu_used} RESP: #{resp_time}ms PATH: #{path}"
        puts "******* END OF PROCESO INFORMATION *******"
        puts
      end
    end

    def self.subscribe(&blk)
      return unless defined?(ActiveSupport::Notifications)
      ActiveSupport::Notifications.subscribe(SUBSCRIPTION, &blk)
    end

    attr_reader :app, :pid, :notifier

    def initialize(app)
      @app = app
      @notifier ||= ActiveSupport::Notifications if defined?(ActiveSupport::Notifications)
      @pid = Process.pid
    end

    def call(env)
      measure_process_usage(env) do
        @app.call(env)
      end
    end

    def measure_process_usage(env)
      mem_1   = process.mem_size
      cpu_1   = process.user_cpu_times
      resp_1  = Time.now.to_i
      response = yield
      mem_2 = process.mem_size
      cpu_2 = process.user_cpu_times
      resp_2  = Time.now.to_i
      process_usage = process_info(env, (mem_2 - mem_1), (cpu_2 - cpu_1), (resp_2 - resp_1))
      notifier.instrument(SUBSCRIPTION, process_usage)
      response
    end

    def process_info(env, mem_used, cpu_used, resp_time)
      req = Rack::Request.new(env)
      {
        pid: process.pid,
        mem_used: mem_used,
        cpu_used: cpu_used,
        resp_time: resp_time,
        request: req
      }
    end

    def process
      @process ||= Proceso::PID.new(pid)
    end

  end
end

