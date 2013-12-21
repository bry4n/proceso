module Proceso
  extend self

  def processes
    pids.map do |i|
      Proceso::PID.new(i)
    end
  end

end

case RUBY_PLATFORM
when /linux/
  require 'proceso/linux'
when /darwin/
  require 'proceso/darwin'
end

require 'proceso/pid'

if defined?(Rails) || defined?(Rack)
  require 'proceso/middleware'
end