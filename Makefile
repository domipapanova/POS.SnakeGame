
# Define the C++ compiler and flags.
CXX = g++
CXXFLAGS = -std=c++14 -Wall

# Define the source files and object files.
SERVER_SOURCES = main.cpp Server.cpp Server.h Game.cpp Game.h Grid.cpp Grid.h Snake.cpp Snake.h Output.cpp Output.h Consts.h
CLIENT_SOURCES = main.cpp Client.cpp Client.h Output.cpp Output.h Consts.h
SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o)

# Define the build targets.
all: server client

server: $(SERVER_OBJECTS) $(CXX) $(CXXFLAGS) $(SERVER_OBJECTS) -o server pthread

client: $(CLIENT_OBJECTS) $(CXX) $(CXXFLAGS) $(CLIENT_OBJECTS) -o client pthread

# Define the clean target.
clean: rm -f server client $(SERVER_OBJECTS) $(CLIENT_OBJECTS)