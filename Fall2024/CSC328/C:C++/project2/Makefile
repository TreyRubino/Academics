# Trey Rubino

all: p2

p2: main.o sort.o utility.o
	gcc main.o sort.o utility.o -o p2 -lpthread

main.o: main.c sort.h
	gcc -c main.c

sort.o: sort.c sort.h
	gcc -c sort.c

utility.o: utility.c utility.h
	gcc -c utility.c

clean:
	rm *.o p2

submit:
	~schwesin/bin/submit cpsc328 project2

.PHONY: clean submit
