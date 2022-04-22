

test: test.c structures.c hold_queue1.c
	cc -o test test.c structures.c hold_queue1.c

clean:
	rm *.o test
