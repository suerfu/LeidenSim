CC = g++ -std=c++11

all : ProcessTrack

test : testPulse testPulseArray

ProcessTrack : ProcessTrack.cpp ./src/TrackReader.cpp ./src/MCPulse.cpp ./src/MCPulseArray.cpp 
	$(CC) -I./include $^ -o $@ `root-config --cflags --glibs`

testPulse : testPulse.cpp ./src/MCPulse.cpp
	$(CC) -I./include $^ -o $@

testPulseArray : testPulseArray.cpp ./src/MCPulse.cpp ./src/MCPulseArray.cpp
	$(CC) -I./include $^ -o $@

clean :
	rm ProcessTrack
