require 'bundler/setup'
lib_path = File.join(File.dirname(__FILE__), "..", "lib")
$LOAD_PATH.unshift(lib_path) unless $LOAD_PATH.include?(lib_path)

require 'debugger'
require "proceso"
