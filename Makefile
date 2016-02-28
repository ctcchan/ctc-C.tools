CC=g++
CFLAGS= -std=c++11 -Wall -w
INCLUDE:= -Iinclude/
SOURCE:= $(wildcard src/*.cpp)
TARGET=ctools

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCE) -o $(TARGET)

clean:
	rm -rf $(TARGET)
