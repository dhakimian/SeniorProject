CXX = g++
#CXX = clang++
PREFIX = /opt/local
SDL_LIB = `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net
SDL_INCLUDE = `sdl2-config --cflags`
CXXFLAGS = -Wall -c -std=c++0x $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)

SRC = src/server/
BUILD = build
VPATH = $(SRC):$(BUILD)
SOURCES=$(notdir $(wildcard $(SRC)/*.cpp))
OBJECTS=$(SOURCES:.cpp=.o)
EXE = server

all: $(SOURCES) $(BUILD) $(EXE)
		
$(EXE): $(OBJECTS)
		$(CXX) $(addprefix $(BUILD)/,$(notdir $^)) $(LDFLAGS) -o $@

.cpp.o:
		$(CXX) $< $(CXXFLAGS) -o $(BUILD)/$@

# Make sure the build directory exists
$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm $(BUILD)/*.o; rm $(EXE)
