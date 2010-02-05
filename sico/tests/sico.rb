#!/usr/bin/ruby
require 'SICemu'

if ARGV.length != 1
    puts "usage: sico <file.sico>"
    exit
end

emul = SICemu.new()
emul.load_object(ARGV[0])
emul.set_var('t', 0x00000100)
emul.set_var('A', 0x00000104)
emul.set_var('B', 0x00000108, value=10)
emul.show_variables
emul.run(trace=true)
emul.show_variables
