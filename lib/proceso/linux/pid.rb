module Proceso
  class PID

    include Proceso::Proc

    def initialize(pid)
      @pid = pid
    end

    def running?
      !!(Process.getpgid(pid) rescue false)
    end

    def command
      cmd = proc_info("comm")
      `which #{cmd}`.strip
    end

    def executable
      proc_info("comm")
    end

    def resident_size
      pid_stat["rss"].to_i
    end

    def virtual_size
      pid_stat["vsize"].to_i
    end

    def cpu_usage
      cpu_1 =  user_cpu_times
      sleep 0.5
      cpu_2 =  user_cpu_times
      NCPU.to_f * (cpu_2.to_f - cpu_1.to_f) * 100.0
    end

    def user_cpu_times
      pid_stat["utime"].to_f
    end

    def system_cpu_times
      pid_stat["stime"].to_f
    end

  end
end
