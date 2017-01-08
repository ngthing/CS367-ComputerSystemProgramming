p4:	p4.o log.o
	gcc -o p4 p4.o log.o

p4.o: p4.c log.h
	gcc -c p4.c

log.o: log.c log.h
	gcc -c log.c

clean:	
	rm -f *.o p4