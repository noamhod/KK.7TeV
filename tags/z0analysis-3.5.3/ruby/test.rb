#!/usr/bin/env ruby

def status(st=0)
	if(st==0) then
		puts "Success: $?=#{st}"
	else
		puts "Error: $?=#{st}"
	end
end

#%x(ls tmp/)
#status($?)
#%x(ls /tmp)
#status($?)

%x(qstat | grep hod > /dev/null)
status($?)
