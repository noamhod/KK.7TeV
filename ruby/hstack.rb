#!/usr/bin/env ruby

workdir = "../run";
thisdir = Dir.getwd();
Dir.chdir(workdir);
root = "$ROOTSYS/bin/root.exe -b -l -q"

#noTmplts_noEWkFsig_noCoupScale
#       noEWkFsig_noCoupScale

inlist =
[
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=Nvxp_no_puwgt    --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=Nvxp_with_puwgt  --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=Mass             --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=MassNumbers      --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=Mass_limit_      --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=pTLeading        --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=pTSubleading     --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=EtaLeading       --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=EtaSubleading    --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=PhiLeading       --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=PhiSubleading    --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=EtaQ             --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=QT               --istru=0",
	"#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=yQ               --istru=0",
	# "#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=IsolationFull    --istru=0",
	# "#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=IsolationLow     --istru=0",
	# "#{root} hstack.C+ --ftype=noTmplts_noEWkFsig_noCoupScale --htype=MassAntiIsolated --istru=0",
]
outlist = []

system(inlist[0]);

inlist.each{ |histogram|
	if(histogram==inlist[0]) then next; end
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
