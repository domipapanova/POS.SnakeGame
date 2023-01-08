# Define the C++ compiler and flags.
CXX = g++

# Define the source files and object files.
SERVER_SOURCES = main.cpp Server.cpp Client.cpp Game.cpp Grid.cpp Snake.cpp Output.cpp
CLIENT_SOURCES = main.cpp Server.cpp Client.cpp Game.cpp Grid.cpp Snake.cpp Output.cpp
SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o)

all: server client

server: $(SERVER_OBJECTS)
	$(CXX) $(SERVER_SOURCES) -o SnakeGame
	./SnakeGame server $(PORT)

client: $(CLIENT_OBJECTS)
	$(CXX) $(CLIENT_SOURCES) -o SnakeGame
	./SnakeGame client $(IP) $(PORT)

clean:
	rm -f server client $(SERVER_OBJECTS) $(CLIENT_OBJECTS) SnakeGame
