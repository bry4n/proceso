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
     proc(pid, "cmdline")
   end

   def executable
     proc(pid, "comm")
   end

   def path
     command.gsub(/\s-.*$/,'')
   end

   def resident_size
     pid_stat["rss"].to_i
   end

   def virtual_size
     pid_stat["vsize"].to_i
   end

   def cpu_usage
     0.0
   end

   def user_cpu_times
     0.0
   end

   def system_cpu_times
     0.0
   end

 end
end