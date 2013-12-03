lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)

require 'diablo/version'


Gem::Specification.new do |spec|
  spec.name         = "diablo"
  spec.version      = Diablo::VERSION
  spec.authors      = ["Bryan Goines"]
  spec.email        = ["bryann83@gmail.com"]
  spec.description  = %q{Will update this later}
  spec.summary      = %q{Will update this later}
  spec.homepage     = "https://github.com/bry4n"
  spec.license      = "MIT"

  spec.files        = Dir["lib/**/*.rb"]
#  spec.executables  = ["diablo"]
  spec.test_files   = Dir["spec/**/*.rb"]
  spec.require_paths << "ext/diablo_ext"
  spec.extensions << "ext/diablo_ext/extconf.rb"

#  spec.add_dependency "something"

  spec.add_development_dependency "rake"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "rspec"
  spec.add_development_dependency "rubygems-tasks"
end
