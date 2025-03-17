CXX = g++
CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

# Executables
all: dijkstras_main ladder_main

# Compile dijkstra's algorithm executable
dijkstras_main: src/dijkstras_main.cpp src/dijkstras.cpp
	$(CXX) $(CXXFLAGS) src/dijkstras_main.cpp src/dijkstras.cpp -o dijkstras_main

# Compile ladder problem executable
ladder_main: src/ladder_main.cpp src/ladder.cpp
	$(CXX) $(CXXFLAGS) src/ladder_main.cpp src/ladder.cpp -o ladder_main

# Clean up generated files
clean:
	/bin/rm -f dijkstras_main ladder_main
