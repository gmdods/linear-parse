CC = gcc
CFLAGS = -O2 -Wall -Wextra -Wpedantic -std=c++17 \
	-fno-stack-protector -fno-common -march=native

.PHONY: all
all: linear.o

linear.o: linear.cpp linear.hpp
	$(CC) -o $@ -c $(CFLAGS) $<

test.out: test.cpp linear.o
	$(CC) -o $@ $(CFLAGS) -ggdb3 $^

.PHONY: test
test: test.out
	./test.out && rm test.out

.PHONY: clean
clean:
	rm *.o *.out
