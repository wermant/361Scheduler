all: scheduler

scheduler: main.c 
	cc -o scheduler main.c 
clean:
	rm *.o test
