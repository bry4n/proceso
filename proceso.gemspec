lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)

require 'proceso/version'

Gem::Specification.new do |spec|
  spec.name         = "proceso"
  spec.version      = Proceso::VERSION
  spec.authors      = ["Bryan Goines"]
  spec.email        = ["bryann83@gmail.com"]
  spec.description  = %q{Easiest way to retrieve the process information}
  spec.summary      = %q{Simple process information gather}
  spec.homepage     = "https://github.com/bry4n/proceso"
  spec.license      = "MIT"

  spec.files        = Dir["lib/**/*.rb", "ext/**/*"]
  spec.test_files   = Dir["spec/**/*.rb"]
  spec.require_paths << "ext/proceso"

  spec.extensions << "ext/proceso/extconf.rb"

  spec.add_dependency "rack"

  spec.add_development_dependency "rake"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "rspec"
  spec.add_development_dependency "rubygems-tasks"
end
