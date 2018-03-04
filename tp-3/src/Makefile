all: functions
functions: functions.o main.o
	gcc -g functions.o main.o -o tp3 -lpthread
main.o: main.c functions.h
	gcc -g -c main.c -Wall
functions.o: functions.h functions.c
	gcc -g -c functions.c -Wall
clean:
	rm *.o
	rm tp3
