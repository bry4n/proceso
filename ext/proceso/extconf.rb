if RUBY_PLATFORM =~ /darwin/

  require "mkmf"

  RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

  platform = RbConfig::CONFIG["target_os"]

  # TODO: Add Linux Support
  # if platform =~ /linux/
  #   include_dirs = ["/usr/include", "/usr/local/include"]
  #   unless have_header("proc/readproc.h")
  #     abort "proc/readproc.h is missing - please install libproc-dev"
  #   end
  #   have_library("procps")
  # end

  create_makefile('proceso/darwin/proceso')
end
