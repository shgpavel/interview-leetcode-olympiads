CFLAGS := -Wall -Wextra -Wconversion -Wformat -Wformat-security \
-O3 -std=c2x ${CFLAGS}
# -fsanitize=address -fsanitize=undefined

CC = gcc
LD = gcc

SRCS = main.c
STYLE = google

LL =

main: $(SRCS)
	$(CC) $(SRCS) -o main.o $(LL) $(CFLAGS)

format: $(SRCS)
	clang-format -style=$(STYLE) -i $(SRCS)

clean:
	rm -rf main.o
