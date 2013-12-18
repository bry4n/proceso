require "mkmf"

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

platform = RbConfig::CONFIG["target_os"]

if platform =~ /linux/
  unless have_header("proc/readproc.h")
    abort "proc/readproc.h is missing - please install libproc-dev"
  end
end

create_makefile('proceso/proceso')
