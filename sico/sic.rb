#!/usr/bin/ruby
require 'SICemu'

if ARGV.length != 1
    puts "usage: sico <file.sic>"
    exit
end

emul = SICemu.new()

puts "Setting variables..."
emul.set_variable("B", 10)

puts "Loading file..."
emul.load_file(ARGV[0])

puts "Dumping variables..."
emul.show_variables

puts "Starting program..."
emul.run(trace=true)

puts "Dumping variables..."
emul.show_variables
