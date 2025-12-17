CC = g++
CFLAGS = -Og -Wall -Wextra -Wpedantic -std=c++20 \
	-fno-stack-protector -fno-common -march=native

.PHONY: all
all: linear.o

linear.o: linear.cpp linear.hpp
	$(CC) -o $@ -c $(CFLAGS) -ggdb3 $<

test.out: test.cpp linear.o
	$(CC) -o $@ $(CFLAGS) -ggdb3 $^

.PHONY: test
test: test.out
	valgrind --leak-check=full ./test.out && rm test.out

.PHONY: clean
clean:
	rm *.o *.out
