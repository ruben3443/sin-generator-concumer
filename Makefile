all: generator consumer
generator: generator.o
	gcc generator.o -lm -o generator

consumer: consumer.o
	gcc consumer.o -lm -o consumer

generator.o: generator.c
	gcc -c generator.c

consumer.o: consumer.c
	gcc -c consumer.c

clean:
	rm -f *.o generator consumer shmid.txt