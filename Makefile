CXX      ?= g++
CXXFLAGS  = -O2 $(shell pkg-config --cflags raylib) -Isrc
LDFLAGS   = $(shell pkg-config --libs raylib)
TARGET    = 3d-cube

# Recursively find all .cpp files under src/
SRCS = $(shell find src -name '*.cpp')

# Mirror the src/ tree under build/
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile each .cpp, creating subdirs under build/ as needed
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build $(TARGET)
