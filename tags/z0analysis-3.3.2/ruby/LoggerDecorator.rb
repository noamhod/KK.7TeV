#!/usr/bin/env ruby

# http://blog.gugl.org/archives/category/ruby
# http://www.ruby-doc.org/stdlib/libdoc/logger/rdoc/

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
require 'logger'
include FileUtils

class LoggerDecorator
  def initialize(logger)
    @logger = logger
    logger.datetime_format = "%d/%m/%Y %H:%M:%S "
    #logger.formatter = proc { |severity, datetime, progname, msg|
    #  "#{datetime}: #{msg}\n"
    #}
  end

  %w{debug info warn error fatal}.each do |method|
    eval(<<-eomethod)
      def #{method}(msg)
        @logger.#{method}(position) {msg}
      end
    eomethod
  end

  private
  def position
    caller.at(1).sub(%r{.*/},'').sub(%r{:in\s.*},'')
  end
end

=begin
# Create a logger which logs messages to STDERR/STDOUT.
logger = Logger.new(STDERR)
logger = Logger.new(STDOUT)
=end

=begin
# Create a logger for the file which has the specified name
logger = Logger.new('logfile.log')
=end

=begin
# Create a logger for the specified file.
file = File.open('foo.log', File::WRONLY | File::APPEND)
# To create new (and to remove old) logfile, add File::CREAT like;
#   file = open('foo.log', File::WRONLY | File::APPEND | File::CREAT)
logger = Logger.new(file)
=end

=begin
# set the debug level
logger.level = Logger::WARN
=end

=begin
# instantiate the log decorator 
LOG = LoggerDecorator.new(logger)
=end

=begin
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
=end

=begin
logger.close
=end
