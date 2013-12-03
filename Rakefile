require 'bundler/setup'
require 'bundler/gem_tasks'
require 'rubygems/package_task'
require 'rake/extensiontask'
require 'rake/testtask'
require 'rspec/core/rake_task'
require 'rake/clean'

CLEAN.include(
  "ext/diablo_ext/*.o",
  "ext/diablo_ext/*.bundle"
)

CLOBBER.include(
  "ext/diablo_ext/Makefile",
  "pkg"
)

gem_spec = Gem::Specification.load("diablo.gemspec")

Gem::PackageTask.new(gem_spec) do |pkg|
  pkg.need_zip = true
  pkg.need_tar = true
end

Rake::ExtensionTask.new("diablo_ext", gem_spec)

RSpec::Core::RakeTask.new(:spec)

task :console do
  system("irb -r ./lib/diablo")
end

task :build => [:clean, :compile]
task :default => [:build, :spec]
