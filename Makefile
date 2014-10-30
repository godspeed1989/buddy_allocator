CC=gcc
CFLAGS=-g -Wall
OBJS=buddy.o test.o dump_print.o
HEADERS=buddy.h

all: test

test: $(OBJS)
	$(CC) -o $@ $^

buddy.o: buddy.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

dump_print.o: dump_print.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

test.o: test.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

run: test
	./test
	dot bdgraph.dot -Tpng > bd.png

clean:
	rm -rf *.o test
