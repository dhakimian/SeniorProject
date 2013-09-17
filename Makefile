CXX = g++
#CXX = clang++
SDL_LIB = -L/usr/local/lib/ -lSDL2 -Wl,-rpath=/usr/local/lib/
SDL_INCLUDE = -I/usr/local/include/
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
#CXXFLAGS = -Wall -c -std=c++0x $(SDL_INCLUDE) # uncomment if the above doesn't work (and comment the above)
LDFLAGS = $(SDL_LIB)

SRC = src
BUILD = build
VPATH = $(SRC):$(BUILD)
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXE = our_game

all: $(SOURCES) $(BUILD) $(EXE)
		
$(EXE): $(OBJECTS)
		$(CXX) $(LDFLAGS) $(addprefix $(BUILD)/,$(OBJECTS)) -o $@

.cpp.o:
		$(CXX) $(CXXFLAGS) $< -o $(BUILD)/$@

# Make sure the build directory exists
$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm $(BUILD)/*.o; rm $(EXE)
