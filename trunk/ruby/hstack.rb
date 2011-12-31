#!/usr/bin/env ruby

workdir = "../run";
thisdir = Dir.getwd();
Dir.chdir(workdir);

root = "$ROOTSYS/bin/root.exe -b -l -q"
inlist =
[
	"#{root} hstack.C+ --ftype=noPUrw --htype=Nvxp_no_puwgt   --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=Nvxp_with_puwgt --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=Mass            --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=MassNumbers     --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=Mass_limit_     --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=pTLeading       --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=pTSubleading    --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=EtaLeading      --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=EtaSubleading   --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=PhiLeading      --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=PhiSubleading   --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=QT              --istru=0",
	"#{root} hstack.C+ --ftype=noPUrw --htype=yQ              --istru=0",
]
outlist = []

inlist.each{ |histogram|
	histogram_thread = Thread.new(histogram) { |histo|
		puts "send histo -> #{histo}"
		system(histo)
	}
	outlist << histogram_thread
}

# Wait for the threads to finish
outlist.each { |histogram|
	puts "join histogram -> #{histogram}"
	histogram.join
}

Dir.chdir(thisdir);
