CXX = g++
#CXX = clang++
PREFIX = /opt/local
SDL_LIB = -L$(PREFIX)/lib/ -lSDL2 -lSDL2_image# -Wl,-rpath=$(PREFIX)/lib/
SDL_INCLUDE = -I$(PREFIX)/include/SDL2
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)

SRC = src
BUILD = build
VPATH = $(SRC):$(BUILD)
SOURCES=$(notdir $(wildcard $(SRC)/*.cpp))
OBJECTS=$(SOURCES:.cpp=.o)
#OBJECTS=$(addprefix $(BUILD)/,$(OBJ))
EXE = our_game

all: $(SOURCES) $(BUILD) $(EXE)
		
$(EXE): $(OBJECTS)
		$(CXX) $(addprefix $(BUILD)/,$^) $(LDFLAGS) -o $@

#$(BUILD)/%.o: %.cpp
.cpp.o:
		$(CXX) $< $(CXXFLAGS) -o $(BUILD)/$@

# Make sure the build directory exists
$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm $(BUILD)/*.o; rm $(EXE)
