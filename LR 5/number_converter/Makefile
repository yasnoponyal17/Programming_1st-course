CC = gcc
CFLAGS = -Wall -g
ifdef DEBUG
CFLAGS += -DDEBUG
endif
TARGET = number_converter
SRCDIR = src
INCDIR = include
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/converter.c $(SRCDIR)/validator.c $(SRCDIR)/ui_handler.c
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(INCDIR)/converter.h $(INCDIR)/validator.h $(INCDIR)/ui_handler.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	del /Q $(OBJECTS) $(TARGET).exe 2>nul || rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean