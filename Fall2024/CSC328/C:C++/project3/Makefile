# Trey Rubino

all: webclient

webclient: main.o utility.o socket_utility.o
	gcc main.o utility.o socket_utility.o -o webclient

main.o: main.c utility.h
	gcc -c main.c

utility.o: utility.c utility.h
	gcc -c utility.c

socket_utility.o: socket_utility.c socket_utility.h utility.h
	gcc -c socket_utility.c

clean: 
	rm *.o webclient

submit:
	~schwesin/bin/submit cpsc328 project3

.PHONY: clean submit
