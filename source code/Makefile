CC=g++
LIBS=-lm



extractor: extractor.o FrameSequence.o
	g++ extractor.o FrameSequence.o -o extractor -std=c++20

%.o : %.cpp
	$(CC) -c $< -o $@ -std=c++20


clean:
	rm *.o extractor
	
makeDefaultFilm:
	ffmpeg -r 24 -i sequence2%d.pgm -b:v 5000k sequence2.mp4
	
makeReverseFilm:
	ffmpeg -r 24 -i reversesequence%d.pgm -b:v 5000k reversesequence.mp4
	
makeInverseFilm:
	ffmpeg -r 24 -i invseq%d.pgm -b:v 5000k invseq.mp4
	
makeReinverseFilm:
	ffmpeg -r 24 -i reinverseq%d.pgm -b:v 5000k reinverseq.mp4
	
	
