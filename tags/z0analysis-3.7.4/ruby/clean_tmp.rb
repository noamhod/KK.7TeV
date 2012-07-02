#!/usr/bin/env ruby
%x(rm -f ../run/tmp/*)
%x(rm -f ../run/tmp/err/*)
%x(rm -f ../run/tmp/out/*)
%x(rm -f ../data/tmp/*)
%x(rm -f ../scripts/tmp/*)
%x(rm -f ../conf/tmp/*)

# rm -f ../run/tmp/err/* ../run/tmp/out/* ../run/tmp/* ../scripts/tmp/* ../data/tmp/* ../conf/tmp/*
