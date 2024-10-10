total-counter: total-counter.c
	gcc -o3 -o total-counter total-counter.c -lpthread

total-counter-mutexed: total-counter-mutexed.c
	gcc -o3 -o total-counter-mutexed total-counter-mutexed.c -lpthread

all: total-counter total-counter-mutexed
	
clean:
	rm total-counter total-counter-mutexed
