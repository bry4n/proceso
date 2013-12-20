module Proceso

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