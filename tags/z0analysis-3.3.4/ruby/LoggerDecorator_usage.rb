#!/usr/bin/env ruby

# http://blog.gugl.org/archives/category/ruby
# http://www.ruby-doc.org/stdlib/libdoc/logger/rdoc/

require 'LoggerDecorator'

# Create a logger which logs messages to STDERR/STDOUT.
logger = Logger.new(STDERR)
logger = Logger.new(STDOUT)

# Create a logger for the file which has the specified name
#logger = Logger.new('logfile.log')

=begin
# Create a logger for the specified file.
file = File.open('foo.log', File::WRONLY | File::APPEND)
# To create new (and to remove old) logfile, add File::CREAT like;
#   file = open('foo.log', File::WRONLY | File::APPEND | File::CREAT)
logger = Logger.new(file)
=end

# set the debug level
logger.level = Logger::WARN

# instantiate the log decorator 
LOG = LoggerDecorator.new(logger)



logger.debug "Person attributes hash: from line" # example of direct use of logger

LOG.debug "debug test"   # example of indirect use of logger, via the LoggerDecorator class
LOG.error "error test"   # example of indirect use of logger, via the LoggerDecorator class
LOG.info  "info test"    # example of indirect use of logger, via the LoggerDecorator class
LOG.warn  "warning test" # example of indirect use of logger, via the LoggerDecorator class
LOG.fatal "fatal test"   # example of indirect use of logger, via the LoggerDecorator class


begin
	File.each_line(path) do |line|
		unless line =~ /^(\w+) = (.*)$/
			LOG.error("Line in wrong format: #{line}")
		end
	end
rescue => err
		LOG.fatal("Caught exception; exiting")
		LOG.fatal(err)
end

logger.close
