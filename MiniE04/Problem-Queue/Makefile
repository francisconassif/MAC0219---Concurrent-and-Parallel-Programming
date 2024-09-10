CC = gcc

CFLAGS = -pthread -Wall

TARGETS = safequeue problemqueue

all: $(TARGETS)

safequeue: safequeue.o
	$(CC) $(CFLAGS) -o safequeue safequeue.o

problemqueue: problemqueue.o
	$(CC) $(CFLAGS) -o problemqueue problemqueue.o

safequeue.o: safequeue.c
	$(CC) $(CFLAGS) -c safequeue.c

problemqueue.o: problemqueue.c
	$(CC) $(CFLAGS) -c problemqueue.c

clean:
	rm -f $(TARGETS) *.o
