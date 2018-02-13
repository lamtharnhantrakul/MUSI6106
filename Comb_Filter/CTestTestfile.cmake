# CMake generated Testfile for 
# Source directory: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2
# Build directory: /Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(RingBuff "/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/TestExec" "RingBuff")
add_test(AudioIo "/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/TestExec" "AudioIo" "/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/src/Tests/TestData/")
add_test(CombFilter "/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/TestExec" "CombFilter")
add_test(Dtw "/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/TestExec" "Dtw")
add_test(Vibrato "/Users/yonglianghe/Downloads/2018-MUSI6106-assignment_2/bin/TestExec" "Vibrato")
subdirs("MUSI6106Exec")
subdirs("AudioFileIO")
subdirs("CombFilter")
subdirs("TestExec")
