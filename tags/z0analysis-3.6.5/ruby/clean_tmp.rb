#!/usr/bin/env ruby
%x(rm -f ../run/tmp/*)
%x(rm -f ../run/tmp/err/*)
%x(rm -f ../run/tmp/out/*)
%x(rm -f ../data/tmp/*)
%x(rm -f ../scripts/tmp/*)

# rm -f ../run/tmp/err/* ../run/tmp/out/* ../run/tmp/* ../scripts/tmp/* ../data/tmp/* ../data/*
