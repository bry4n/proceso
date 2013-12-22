require 'proceso'

pid = Proceso::PID.new($$)

puts pid.status
