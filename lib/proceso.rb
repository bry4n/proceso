require 'proceso/proceso'

module Proceso

  class PID

    def path
      File.dirname(self.name)
    end

    def executable
      File.basename(self.name)
    end

  end

end