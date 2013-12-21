require_relative 'linux/proc'
require_relative 'linux/pid'

module Proceso
  extend self

  NCPU = begin
    cpuinfo = File.read("/proc/cpuinfo")
    cpuinfo.strip.split(/\n/).grep(/processor/).count
  end

  def pids
    Dir["/proc/*"].select do
      |x| x =~ /\/\d+$/
    end.map(&File.method(:basename)).map(&:to_i)
  end

end