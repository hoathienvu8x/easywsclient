CXXFLAGS = -std=c++11 -Wall
LDLIBS = -lstdc++ -lpthread

.PHONY: all clean

all: example-client
clean:
	@echo "Cleanning..."
	rm -rf example-client *.o

example-client: example-client.o easywsclient.o
example-thread: example-thread.o easywsclient.o
example-client.o: example-client.cpp easywsclient.h
example-thread.o: example-thread.cpp easywsclient.h
easywsclient.o: easywsclient.cpp easywsclient.h
