# Roadagain's reversi game

CXX = g++
CXXFLAGS = -c -O3 -Wall -Wextra
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
EXE = reversi

.SUFFIXES: .cpp .o .h .d

.PHONY: all
all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) -lncurses

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXE)

.PHONY: rebuild
rebuild: clean all

.cpp.o:
	$(CXX) $(CXXFLAGS) $^
