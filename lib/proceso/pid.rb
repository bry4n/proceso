module Proceso
  class PID

    attr_accessor :pid

    def path
      File.dirname(command)
    end

    def executable
      File.basename(command)
    end

    def mem_size(format = :bytes)
      rss = resident_size
      rss *= 1024 if RUBY_PLATFORM =~ /linux/
      case format.to_s
      when "bytes" then rss
      when "kb", "kilobytes" then rss.to_f / 1024.0
      when "mb", "megabytes" then rss.to_f / 1024.0 / 1024.0
      when "gb", "gigabytes" then rss.to_f / 1024.0 / 1024.0 / 1024.0
      end
    end

  end
end
