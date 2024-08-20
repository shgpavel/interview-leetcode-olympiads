CFLAGS := -Wall -Wextra -Wconversion -Wformat -Wformat-security \
-fsanitize=address -fsanitize=undefined -O1 -std=c2x ${CFLAGS}

CC = gcc
LD = gcc

SRCS = ttr.c main.c
STYLE = google

LL = -lm

main: $(SRCS)
	$(CC) $(SRCS) -o main.o $(LL) $(CFLAGS)

format: $(SRCS)
	clang-format -style=$(STYLE) -i $(SRCS)

clean:
	rm -rf main.o
