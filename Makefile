CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic -I. -g
LDFLAGS=-lGL -lm -lpthread -ldl -lrt -lX11

TARGET=main
SOURCES=main.c quadtree.c
OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) libraylib.a $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(TARGET) $(OBJECTS)
