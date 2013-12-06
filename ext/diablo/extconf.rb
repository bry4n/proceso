require "mkmf"

unless have_library("ruby") || have_header("ruby.h")
  raise "ruby library or ruby.h is not found"
end

create_makefile('diablo')