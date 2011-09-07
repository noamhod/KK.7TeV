#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
include FileUtils

cd("../run")
%x(rm -f *.so *.d)
%x(root -b -l -q compile_for_qsub.C)
cd("../ruby")
