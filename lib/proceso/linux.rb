require_relative 'linux/proc'
require_relative 'linux/pid'

module Proceso
  NCPU = `cat /proc/cpuinfo | egrep "core id|physical id" | tr -d "\n" | sed s/physical/\\nphysical/g | grep -v ^$ | sort | uniq | wc -l`.strip.to_i
end