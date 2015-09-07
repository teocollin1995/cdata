CFLAGS = -std=c11 -Wall -g -O1
CC= gcc

test: test.o linkedlist.o
test.o: linkedlist.h
linkedlist.o: linkedlist.h

debug:
	gcc -std=c11 -Wall -c -o test.o test.c -g -O1
	gcc -std=c11 -Wall test.o linkedlist.o -o test -g


clean:
	rm -f test.o linkedlist.o test
	rm -f linkedlist_test

test_linkedlist:
	checkmk linkedlist_test.check > linkedlist_test.c
	gcc -Wall -o linkedlist_test linkedlist_test.c linkedlist.c -lcheck
