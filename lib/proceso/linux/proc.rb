module Proceso
  module Proc

    def pid_stat
      stat = %w(
        pid comm state ppid pgrp session tty_nr tpgid
        flags minflt cminflt majflt cmajflt utime stime
        cutime cstime priority nice num_threads itrealvalue
        starttime vsize rss rsslim startcode endcode startstack
        kstkesp kstkelp signal blocked sigignore sigcatch
        whcan nswap cnswap exit_signal processor rt_priority
        policy delayacct_blkio_ticks guest_time cguest_time
      )
      info = proc_info()
      resources = {}
      info.split(/ /).each_with_index do |line, i|
        resources[stat[i]] = line
      end
      resources
    end

    def proc_info(type = "stat")
      filename = "/proc/#{pid}/#{type}"
      return unless File.exist?(filename)
      File.read(filename).strip
    end

  end
end
