all: test

test: 
	cc -o test test.c structures.c

clean:
	rm *.o test
