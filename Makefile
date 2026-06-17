CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra -std=c11
TARGET ?= library

SRCS = main.c interface.c management.c book_management.c user_management.c globals.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

ifeq ($(OS),Windows_NT)
clean:
	-del /Q /F *.o *.obj *.exe $(TARGET) 2>NUL
else
clean:
	rm -f $(TARGET) $(OBJS)
endif

.PHONY: all clean
