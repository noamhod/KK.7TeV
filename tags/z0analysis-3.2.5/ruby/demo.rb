#!/usr/bin/env ruby

require 'libRuby'

gROOT.Reset

c1 = TCanvas.new('c1', 'Example with Formula', 200, 10, 700, 500)
c1.Draw
#
# Create a one dimensional function and draw it
#
fun1 = TF1.new('fun1', 'abs(sin(x)/x)', 0, 10)
c1.SetGridx
c1.SetGridy
fun1.Draw
c1.Update

gets