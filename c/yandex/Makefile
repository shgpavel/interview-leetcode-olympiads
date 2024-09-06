CFLAGS := -Wall -Wextra -Wconversion -Wformat -Wformat-security \
-fsanitize=address -fsanitize=undefined -O3 -std=c2x ${CFLAGS}

CC = gcc
LD = gcc

SRCS = A.c
STYLE = google

LL = 

main: $(SRCS)
	$(CC) $(SRCS) -o main.o $(LL) $(CFLAGS)

format: $(SRCS)
	clang-format -style=$(STYLE) -i $(SRCS)

clean:
	rm -rf main.o
