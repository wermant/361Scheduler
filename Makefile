all: scheduler

scheduler: main.c structures.c queues.c display.c
	cc -o scheduler main.c display.c structures.c queues.c
clean:
	rm scheduler
