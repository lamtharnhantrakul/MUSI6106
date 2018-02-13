# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.MUSI6106Exec.Debug:
PostBuild.CombFilter.Debug: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/MUSI6106Exec
PostBuild.AudioFileIO.Debug: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/MUSI6106Exec
PostBuild.sndlib.Debug: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/MUSI6106Exec
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/MUSI6106Exec:\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libCombFilter.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libAudioFileIO.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libsndlib.a
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/MUSI6106Exec


PostBuild.AudioFileIO.Debug:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libAudioFileIO.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libAudioFileIO.a


PostBuild.sndlib.Debug:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libsndlib.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libsndlib.a


PostBuild.CombFilter.Debug:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libCombFilter.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libCombFilter.a


PostBuild.TestExec.Debug:
PostBuild.UnitTest++.Debug: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/TestExec
PostBuild.AudioFileIO.Debug: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/TestExec
PostBuild.sndlib.Debug: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/TestExec
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/TestExec:\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libUnitTest++.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libAudioFileIO.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libsndlib.a
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/debug/TestExec


PostBuild.UnitTest++.Debug:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libUnitTest++.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libUnitTest++.a


PostBuild.MUSI6106Exec.Release:
PostBuild.CombFilter.Release: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/MUSI6106Exec
PostBuild.AudioFileIO.Release: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/MUSI6106Exec
PostBuild.sndlib.Release: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/MUSI6106Exec
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/MUSI6106Exec:\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libCombFilter.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libAudioFileIO.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libsndlib.a
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/MUSI6106Exec


PostBuild.AudioFileIO.Release:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libAudioFileIO.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libAudioFileIO.a


PostBuild.sndlib.Release:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libsndlib.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libsndlib.a


PostBuild.CombFilter.Release:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libCombFilter.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libCombFilter.a


PostBuild.TestExec.Release:
PostBuild.UnitTest++.Release: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/TestExec
PostBuild.AudioFileIO.Release: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/TestExec
PostBuild.sndlib.Release: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/TestExec
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/TestExec:\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libUnitTest++.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libAudioFileIO.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libsndlib.a
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/release/TestExec


PostBuild.UnitTest++.Release:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libUnitTest++.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libUnitTest++.a


PostBuild.MUSI6106Exec.MinSizeRel:
PostBuild.CombFilter.MinSizeRel: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/MUSI6106Exec
PostBuild.AudioFileIO.MinSizeRel: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/MUSI6106Exec
PostBuild.sndlib.MinSizeRel: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/MUSI6106Exec
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/MUSI6106Exec:\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libCombFilter.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libAudioFileIO.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libsndlib.a
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/MUSI6106Exec


PostBuild.AudioFileIO.MinSizeRel:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libAudioFileIO.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libAudioFileIO.a


PostBuild.sndlib.MinSizeRel:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libsndlib.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libsndlib.a


PostBuild.CombFilter.MinSizeRel:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libCombFilter.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libCombFilter.a


PostBuild.TestExec.MinSizeRel:
PostBuild.UnitTest++.MinSizeRel: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/TestExec
PostBuild.AudioFileIO.MinSizeRel: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/TestExec
PostBuild.sndlib.MinSizeRel: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/TestExec
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/TestExec:\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libUnitTest++.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libAudioFileIO.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libsndlib.a
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/MinSizeRel/TestExec


PostBuild.UnitTest++.MinSizeRel:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libUnitTest++.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libUnitTest++.a


PostBuild.MUSI6106Exec.RelWithDebInfo:
PostBuild.CombFilter.RelWithDebInfo: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/MUSI6106Exec
PostBuild.AudioFileIO.RelWithDebInfo: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/MUSI6106Exec
PostBuild.sndlib.RelWithDebInfo: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/MUSI6106Exec
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/MUSI6106Exec:\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libCombFilter.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libAudioFileIO.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libsndlib.a
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/MUSI6106Exec


PostBuild.AudioFileIO.RelWithDebInfo:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libAudioFileIO.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libAudioFileIO.a


PostBuild.sndlib.RelWithDebInfo:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libsndlib.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libsndlib.a


PostBuild.CombFilter.RelWithDebInfo:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libCombFilter.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libCombFilter.a


PostBuild.TestExec.RelWithDebInfo:
PostBuild.UnitTest++.RelWithDebInfo: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/TestExec
PostBuild.AudioFileIO.RelWithDebInfo: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/TestExec
PostBuild.sndlib.RelWithDebInfo: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/TestExec
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/TestExec:\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libUnitTest++.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libAudioFileIO.a\
	/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libsndlib.a
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/relwithdebinfo/TestExec


PostBuild.UnitTest++.RelWithDebInfo:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libUnitTest++.a:
	/bin/rm -f /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libUnitTest++.a




# For each target create a dummy ruleso the target does not have to exist
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libAudioFileIO.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libCombFilter.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libUnitTest++.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/MinSizeRel/libsndlib.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libAudioFileIO.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libCombFilter.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libUnitTest++.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/debug/libsndlib.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libAudioFileIO.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libCombFilter.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libUnitTest++.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/release/libsndlib.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libAudioFileIO.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libCombFilter.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libUnitTest++.a:
/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/lib/relwithdebinfo/libsndlib.a:
