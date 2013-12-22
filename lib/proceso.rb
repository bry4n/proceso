module Proceso
  extend self

  def processes
    pids.map do |i|
      Proceso::PID.new(i)
    end
  end

end
require 'proceso/proceso'
require 'proceso/pid'

if defined?(Rails) || defined?(Rack)
  require 'proceso/middleware'
end
