require 'bundler/setup'
require 'bundler/gem_tasks'
require 'rubygems/package_task'
require 'rake/extensiontask'
require 'rake/testtask'
require 'rspec/core/rake_task'
require 'rake/clean'

CLEAN.include(
  "ext/proceso/*.o",
  "ext/proceso/**/*.o",
  "ext/proceso/*.bundle",
  "ext/proceso/*.so"
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

Rake::ExtensionTask.new("proceso", gem_spec) do |ext|
  ext.lib_dir = "lib/proceso"
end

RSpec::Core::RakeTask.new(:spec)

task :console => [:build] do
  system("irb -r ./lib/proceso")
end
task :build => [:clean, :compile]
task :default => [:build, :spec]
