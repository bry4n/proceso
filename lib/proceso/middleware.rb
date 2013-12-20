require 'rack'

module Proceso
  class Middleware

    SUBSCRIPTION = 'proceso.usage'

    def self.subscribe
      return unless defined?(ActiveSupport::Notifications)
      ActiveSupport::Notifications.subscribe(SUBSCRIPTION) do |*args|
        yield *args
      end
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
      mem_1 = process.mem_size
      cpu_1 = process.user_cpu_times
      response = yield
      mem_2 = process.mem_size
      cpu_2 = process.user_cpu_times
      process_usage = process_info(env, (mem_2 - mem_1), (cpu_2 - cpu_1))
      notifier.instrument(SUBSCRIPTION, process_usage)
      response
    end

    def process_info(env, mem_used, cpu_used)
      req = Rack::Request.new(env)
      {
        pid: process.pid,
        mem_used: mem_used,
        cpu_used: cpu_used,
        request: req
      }
    end

    def process
      @process ||= Proceso::PID.new(pid)
    end

  end
end

