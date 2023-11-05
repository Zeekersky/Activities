all: stackarr

stackarr: driverar.o stackarr.o
	gcc -o stackarr driver.o stackarr.o -lm

driverar.o: driver.c stackarr.o
	gcc -c driver.c

driverl.o: driver.c stackll.o
	gcc -c driver.c

stackarr.o: stackarr.c stack.h
	gcc -c stackarr.c

stackll: driverl.o stackll.o
	gcc -o stackll driver.o stackll.o -lm

stackll.o: stackll.c stack.h
	gcc -c stackll.c

clean:
	rm -f *.o stackarr stackll
