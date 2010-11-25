#!/bin/bash/

scp *.sh hod@lxplus.cern.ch:z0analysis/
scp src/*.C hod@lxplus.cern.ch:z0analysis/src/
scp include/*.h hod@lxplus.cern.ch:z0analysis/include/
scp run/*.C  run/*.h  run/*.sh hod@lxplus.cern.ch:z0analysis/run/
scp conf/*.list conf/*.xml conf/*.cuts conf/*.data hod@lxplus.cern.ch:z0analysis/conf/
scp scripts/*.sh hod@lxplus.cern.ch:z0analysis/scripts/
