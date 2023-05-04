TARGET = test

CC = g++
OPT_FLAGS   = -O3 -g
OTHER_FLAGS = -fsanitize=leak
CFLAGS = $(OPT_FLAGS)

TEST_DIR = ./Test/
SRC_DIR = ./Source/
ROOT_DIR = ./

SRC = 	$(TEST_DIR)Test.cpp 	\
		$(SRC_DIR)List.cpp

LIBS =  ./Libs/Logging/Log.cpp

all: compile run

compile:
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(ROOT_DIR)$(TARGET)

run:
	./$(TARGET)

clean: clean_files clean_dumps

clean_files:
	rm -f *.o $(ROOT_DIR)$(TARGET)

clean_dumps:
	rm -f ./ListDump/GraphDumpImages/*
