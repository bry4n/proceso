module Proceso
  class PID

    attr_accessor :pid

    alias exists? running?

    def path
      File.dirname(command)
    end

    def executable
      File.basename(command)
    end

    def resource
      @resource ||= Proceso::Resource.new(pid);
    end

  end
end