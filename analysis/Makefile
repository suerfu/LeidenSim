CC = g++

all : ProcessTrack

ProcessTrack : ProcessTrack.cpp 
	$(CC) -I./include ProcessTrack.cpp ./src/TrackReader.cpp -o ProcessTrack `root-config --cflags --glibs`

clean :
	rm ProcessTrack
