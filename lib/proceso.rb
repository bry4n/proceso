require 'proceso/proceso'
require 'proceso/pid'
require 'proceso/resource'

module Proceso
  extend self

  def processes
    @pids ||= begin
      pids.map do |pid|
        Proceso::PID.new(pid);
      end
    end
  end

end