
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -O2 -Iinclude
TARGET=sltm
SRCS=src/*.c


all: $(TARGET)


$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)


clean:
	rm -f $(TARGET)
