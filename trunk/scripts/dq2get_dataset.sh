#!/bin/bash/

prefix=user.hod.WZphys

runnumber=$1

subjob=$2

day=d$3

hour=h$4

dq2-list-files $prefix.$runnumber.$subjob.$day.$hour/ > $prefix.$runnumber.$subjob.$day.$hour.listfiles
#dq2-list-files $prefix.$runnumber.$subjob.$day.$hour/

dq2-get $prefix.$runnumber.$subjob.$day.$hour/
