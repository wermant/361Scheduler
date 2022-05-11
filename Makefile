all: scheduler

scheduler: main.c structures.c display.c hold_queue1.c
	cc -o scheduler main.c display.c hold_queue1.c hold_queue2.c structures.c
clean:
	rm *.o test
