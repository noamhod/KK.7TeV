#!/bin/bash/

scp *.sh                                                hod@lxplus.cern.ch:rel16/z0analysis-test/
scp src/*.C                                             hod@lxplus.cern.ch:rel16/z0analysis-test/src/
scp include/*.h                                         hod@lxplus.cern.ch:rel16/z0analysis-test/include/
scp run/*.C  run/*.h  run/*.sh run/listfiles* run/*.txt hod@lxplus.cern.ch:rel16/z0analysis-test/run/
scp conf/*.list conf/*.xml conf/*.cuts conf/*.data      hod@lxplus.cern.ch:rel16/z0analysis-test/conf/
scp scripts/*.sh scripts/*.screen_*                     hod@lxplus.cern.ch:rel16/z0analysis-test/scripts/
