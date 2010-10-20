#!/bin/bash/

prefix=user.hod.WZphys

runnumber=$1

<<<<<<< .mine
=======
day=d$2

>>>>>>> .r127
hour=h$3

dq2-list-files $prefix.$runnumber.$day.$hour/ > $prefix.$runnumber.$day.$hour.listfiles

<<<<<<< .mine
dq2-list-files $prefix.$runnumber.$day.$hour/ > $prefix.$runnumber.$subjob.$day.$hour.listfiles
#dq2-list-files $prefix.$runnumber.$subjob.$day.$hour/

dq2-get $prefix.$runnumber.$day.$hour/
=======
dq2-get $prefix.$runnumber.$day.$hour/
>>>>>>> .r127
