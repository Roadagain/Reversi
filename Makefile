# Roadagain's reversi game

CXX = g++
CXXFLAGS = -c -O3 -Wall -Wextra
SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.cpp)
BUILDDIR = build
OBJ = $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(patsubst %.cpp, %.o, $(SRC)))

.PHONY: all
all:
