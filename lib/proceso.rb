require 'proceso/proceso'
require 'proceso/pid'

module Proceso
  extend self

  def current
    @current ||= Proceso::PID.new(Process.pid)
  end

end

if defined?(Rails) || defined?(Rack)
  require 'proceso/middleware'
end
