for ((i=1;i<=1;i++))

do 	
	echo "run 1" &&
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./deb -list piano.wav 2> valgrindList.txt;

	echo "run 2 " &&
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./deb -mono LRMonoPhase4.wav 2> valgrindMono.txt;

	echo "run 3 " &&
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./deb -mix LRMonoPhase4.wav piano.wav 2> valgrindMix.txt;

	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./deb -chop piano.wav 2 4 2> valgrindChop.txt;

	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./deb -reverse piano.wav 2> valgrindReverse.txt;

	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./deb -enodeText piano.wav hello.txt 2> valgrindEncode.txt;

	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./deb -decodeText encoded-piano.wav 10 out.txt 2> valgrindDecode.txt;

	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./deb -changeSpeed piano.wav 1.25 2> valgrindSpeed.txt;

	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./deb -cut piano.wav 2 4 2> valgrindCut.txt;
	
done;
