# Roadagain's reversi game

CXX = g++
CXXFLAGS = -c -O3 -Wall -Wextra
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
EXE = reversi

.SUFFIXES: .cpp .o .h .d

.PHONY: all
all: $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) -lncurses

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXE)

.cpp.o:
	$(CXX) $(CXXFLAGS) $^
