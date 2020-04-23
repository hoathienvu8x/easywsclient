CXXFLAGS = -std=c++11 -Wall
LDLIBS = -lstdc++

.PHONY: all clean

all: example
clean:
	@echo "Cleanning..."
	rm -rf example *.o

example:example.o websocket.o
example.o: example.cpp websocket.h
websocket.o: websocket.cpp websocket.h


