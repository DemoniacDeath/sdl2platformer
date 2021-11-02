CC=g++
EXECUTABLE=bin/sdl2platformer
SOURCES := $(wildcard ./*.cpp)
OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS=-c -g -std=c++14 -Wall -Werror

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

obj/%.o: ./%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean: cleanobj
	rm $(EXECUTABLE)

cleanobj:
	rm obj/*.o
run: all
	./$(EXECUTABLE)
