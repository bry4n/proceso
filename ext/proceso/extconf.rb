require "mkmf"

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

def have_platform(name)
  have_header("#{name}.h")
  $objs.unshift "#{name}.o"
end


$objs = ["utility.o", "pid.o", "proceso.o"]
case RUBY_PLATFORM
when /linux/ then have_platform("linux")
when /darwin/ then have_platform("darwin")
else
  raise "#{RUBY_PLATFORM} is not currently supported. Send Pull Request for platform support"
end

create_makefile('proceso/proceso')