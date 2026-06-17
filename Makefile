CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra -std=c11
TARGET ?= library

SRCS = main.c interface.c management.c book_management.c user_management.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
