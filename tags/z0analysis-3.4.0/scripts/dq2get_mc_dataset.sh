#!/bin/bash/

prefix=user.hod.mcWZphys

runnumber=$1

day=d$2

hour=h$3

dq2-list-files $prefix.$runnumber.$day.$hour/ > $prefix.$runnumber.$day.$hour.listfiles

dq2-get $prefix.$runnumber.$day.$hour/
