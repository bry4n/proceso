require 'bundler/setup'
require 'bundler/gem_tasks'
require 'rubygems/package_task'
require 'rake/extensiontask'
require 'rake/testtask'
require 'rspec/core/rake_task'
require 'rake/clean'

CLEAN.include(
  "ext/proceso/*.o",
  "ext/proceso/*.bundle"
)

CLOBBER.include(
  "ext/proceso/Makefile",
  "pkg"
)

gem_spec = Gem::Specification.load("proceso.gemspec")

Gem::PackageTask.new(gem_spec) do |pkg|
  pkg.need_zip = true
  pkg.need_tar = true
end

if RUBY_PLATFORM =~ /darwin/
  Rake::ExtensionTask.new("proceso", gem_spec) do |ext|
    ext.lib_dir = "lib/proceso/darwin"
  end
  task :build => [:clean, :compile]
  task :default => [:build, :spec]
else
  task :default => [:spec]
end

RSpec::Core::RakeTask.new(:spec)

task :console do
  system("irb -r ./lib/proceso")
end
