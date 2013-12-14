require 'proceso/proceso'

module Proceso

  class PID

    alias exists? running?

    def path
      File.dirname(self.command)
    end

    def executable
      File.basename(self.command)
    end

  end

end