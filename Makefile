CXX = g++
CXXFLAGS = -std=c++17 -I. -I./includes
LDFLAGS = -L./lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard *.cpp) $(wildcard src/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
