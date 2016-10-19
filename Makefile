# Roadagain's reversi game

CXX = g++
CXXFLAGS = -c -O3 -Wall -Wextra -std=c++11 -MMD
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
DEP = $(patsubst %.cpp, %.d, $(SRC))
LIBFLAGS = -lncurses -largp
EXE = reversi

.SUFFIXES: .cpp .o .h .d

.PHONY: all
all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) $(LIBFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(DEP) $(EXE)

.PHONY: rebuild
rebuild: clean all

.cpp.o:
	$(CXX) $(CXXFLAGS) $^

-include $(DEP)
