CXX = g++
#CXX = clang++
PREFIX = /usr/local
SDL_LIB = -L$(PREFIX)/lib/ -lSDL2 -Wl,-rpath=$(PREFIX)/lib/
SDL_INCLUDE = -I$(PREFIX)/include/
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
#if make fails then change the above from c++11 to c++0x
LDFLAGS = $(SDL_LIB)

SRC = src
BUILD = build
VPATH = $(SRC):$(BUILD)
SOURCES=$(notdir $(wildcard $(SRC)/*.cpp))
OBJECTS=$(SOURCES:.cpp=.o)
EXE = our_game

all: $(SOURCES) $(BUILD) $(EXE)
		
$(EXE): $(OBJECTS)
		$(CXX) $(addprefix $(BUILD)/,$^) $(LDFLAGS) -o $@

.cpp.o:
		$(CXX) $< $(CXXFLAGS) -o $(BUILD)/$@

# Make sure the build directory exists
$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm $(BUILD)/*.o; rm $(EXE)
