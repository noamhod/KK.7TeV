#!/usr/bin/env ruby
require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
require 'LoggerDecorator'
include FileUtils

thisdir=pwd()

`cd #{thisdir}/../run`
system("root -b -l -q #{thisdir}/../run/macro_run.C  1")
#system("cd -")
