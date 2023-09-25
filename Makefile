CC = gcc
#CFLAGS = -Wall -Wextra -g
TARGET = csp

SRCS = main.c generator.c backtrack.c

OBJS = $(SRCS:.c=.o)

HEADERS = headers.h

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)
