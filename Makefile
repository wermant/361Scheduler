

test: test.c structures.c hold_queue1.c hold_queue2.c
	cc -o test test.c structures.c hold_queue1.c hold_queue2.c

clean:
	rm *.o test
