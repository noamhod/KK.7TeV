#!/usr/bin/env ruby
%x(qselect -u $USER | xargs qdel)
# qselect -u $USER -s R | xargs qdel # Delete all your running jobs
# qselect -u $USER -s Q | xargs qdel #Delete all your queued jobs
