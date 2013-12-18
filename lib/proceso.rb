
case RUBY_PLATFORM
when /linux/
  require 'proceso/linux'
when /darwin/
  require 'proceso/darwin'
end

module Proceso

end

require 'proceso/pid'
require 'proceso/resource'