CC=gcc
CFLAGS=-c -Wall

mf_rt_malloc_test: mf_rt_malloc_test.o
	$(CC) mf_rt_malloc_test.o -o mf_rt_malloc_test

mf_rt_malloc_test.o: mf_rt_malloc_test.c
	$(CC) $(CFLAGS) -c mf_rt_malloc_test.c

clean:
	rm -f *.o; rm -f mf_rt_malloc_test
