CC = gcc
CFLAGS = -Wall -g
ifdef DEBUG
CFLAGS += -DDEBUG
endif
TARGET = number_converter
SOURCES = main.c converter.c validator.c ui_handler.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean