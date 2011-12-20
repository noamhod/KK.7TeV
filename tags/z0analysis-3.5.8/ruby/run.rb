#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
include FileUtils

cd("../run")
%x(root -b -l -q macro_run.C)
cd("../ruby")
