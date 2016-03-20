CC=g++
EXECUTABLE=bin/linux/sdl2platformer
SOURCES := $(wildcard SDL2Platformer/*.cpp)
OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
LDFLAGS := -lSDL2
CFLAGS=-c -std=c++11 -Wall -Werror

all: $(SOURCES) $(EXECUTABLE) cleanobj

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

obj/%.o: SDL2Platformer/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean: cleanobj
	rm $(EXECUTABLE)

cleanobj:
	rm obj/*.o
run: all
	./$(EXECUTABLE)
