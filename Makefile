TARGET = test

CC = g++
CFLAGS = -g -fsanitize=address

TEST_DIR = ./
SRC_DIR = ./Source/
ROOT_DIR = ./

SRC = 	$(TEST_DIR)Test.cpp		\
		$(SRC_DIR)List.cpp

$(TARGET) :
	$(CC) $(CFLAGS) $(SRC) -o $(ROOT_DIR)$(TARGET)

clean :
	rm -f *.o $(ROOT_DIR)$(TARGET)
