# comments are always a great idea.

# we use this variable as $(CC) when building commands.
CC=gcc

# we keep using these flags in combination, so they're
# stuffed into a variable. Saves us from having to 
# re-type them repeatedly, and of course we can then
# change it in one place for all uses.
CFLAGS=-O0 -std=c99

# see below for the hwk4 target.
all: hwk4

# the command 'make clean' should remove all generated files.
clean:
	-rm -rf *~ *# *.o hwk4.s hwk4.o hwk4

# target hwk4 builds the overall executable, hwk4.
# depends on all the individual functions' object files.
hwk4: hwk4.o mul_20.o longlog.o collatz.o prime.o caller.o sum_primes.o
	$(CC) $(CFLAGS) -o hwk4 hwk4.o mul_20.o longlog.o collatz.o prime.o caller.o sum_primes.o

# compiles hwk4.c into hwk4.s; needs no other files.
hwk4.s: hwk4.c
	$(CC) $(CFLAGS) -S hwk4.c

# compiles hwk4.s into hwk4.o; needs no other files.
hwk4.o: hwk4.s
	$(CC) $(CFLAGS) -c hwk4.s

# each of the four remaining targets also compiles
# each .s file into the corresponding .o file, with
# no other dependencies on other files.

mul_20.o: mul_20.s
	$(CC) $(CFLAGS) -c mul_20.s

longlog.o: longlog.s
	$(CC) $(CFLAGS) -c longlog.s

collatz.o: collatz.s
	$(CC) $(CFLAGS) -c collatz.s

prime.o: prime.s
	$(CC) $(CFLAGS) -c prime.s

caller.o: caller.s
	$(CC) $(CFLAGS) -c caller.s

sum_primes.o: sum_primes.s
	$(CC) $(CFLAGS) -c sum_primes.s

