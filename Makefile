VERSION = 0.0.1

CC      = clang

CFLAGS  = --std=c++11
LDFLAGS = -lSDL -lGL -lGLU -lstdc++

SRC	= src
BIN	= bin
TARGET  = $(BIN)/pixelsnake
SRCFILES	:= $(wildcard $(SRC)/*.cpp)

all: $(TARGET)

$(TARGET): $(BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCFILES) -o $@

debug: CFLAGS += -g
debug: clean
debug: all

.PHONY: clean
clean:
	$(RM) $(BIN)/*

$(BIN):
	mkdir -p $@

.PHONY: format
format:
	astyle -n -r --style=linux *.c *.h
