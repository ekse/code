#!/usr/bin/ruby
#
# ossec-syscheck-listfiles
# 2009 - Sebastien Duquette (ekse.0x@gmail.com)
#
# Prints the list of files monitored by syscheck.
# The queue files can be found in /var/ossec/queue/syscheck/
#
# The most recent discovered files are printed at the end,
# this command can be combined with tail to show the list
# of last discovered files.
#

if (ARGV.length != 1) then
   puts "usage: ossec-syscheck-files <syscheck_queue_file>"
   puts "The queue files are located in /var/ossec/queue/syscheck/"
   exit
end

begin
   if ( ARGV[0] =~ /^\// ) then
       filename = ARGV[0]
   else
       filename = Dir.pwd + "/" + ARGV[0]
   end
   f = File.open(filename, 'r')

rescue Errno::ENOENT
   puts "Can't read file #{filename}"
   exit
end

f.each_line do |line|
   if (line =~ /^\+\+\+\S+\s\S+\s(.+)/) then
       puts $1
   end
end

f.close
