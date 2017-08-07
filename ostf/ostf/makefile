CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=
SOURCES=Source.cpp core/EventSerializer.cpp core/JsonBuffer.cpp core/net/Peer.cpp events/CreateLobbyEvent.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ostf

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
