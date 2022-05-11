all: scheduler

scheduler: main.c structures.c display.c queues.c
	cc -o scheduler main.c display.c structures.c queues.c
clean:
	rm scheduler
