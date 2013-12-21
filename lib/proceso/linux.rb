require_relative 'linux/proc'
require_relative 'linux/pid'

module Proceso

  extend self

  NCPU = `cat /proc/cpuinfo | egrep "core id|physical id" | tr -d "\n" | sed s/physical/\\nphysical/g | grep -v ^$ | sort | uniq | wc -l`.strip.to_i

  def pids
    Dir["/proc/*"].select do
      |x| x =~ /\/\d+$/
    end.map(&File.method(:basename)).map(&:to_i)
  end

end