CC = gcc
CFLAGS  = -std=gnu11 -Wall -pedantic -O3 -g -fsanitize=address -fno-omit-frame-pointer

.PHONY: clean
clean:
	rm -f *.o
	rm -f main

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

main: elf.o main.o
	$(CC) $(CFLAGS) -o $@ $^