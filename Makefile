CXXFLAGS = -std=c++11 -Wall
LDLIBS = -lstdc++

.PHONY: all clean

all: example-client
clean:
	@echo "Cleanning..."
	rm -rf example-client *.o

example-client:example-client.o easywsclient.o
example-client.o: example-client.cpp easywsclient.h
easywsclient.o: easywsclient.cpp easywsclient.h


