auto-mutex: src/auto-mutex.c
	gcc -o3 -o build/auto-mutex src/auto-mutex.c -lpthread

total-counter: src/total-counter.c
	gcc -o3 -o build/total-counter src/total-counter.c -lpthread

total-counter-mutexed: src/total-counter-mutexed.c
	gcc -o3 -o build/total-counter-mutexed src/total-counter-mutexed.c -lpthread

all: total-counter total-counter-mutexed auto-mutex
	
clean:
	rm ./build/*
