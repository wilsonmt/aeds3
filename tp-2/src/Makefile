functions: functions.o main.o
	gcc functions.o main.o -o tp2
main.o: main.c functions.h
	gcc -g -c main.c
functions.o: functions.h functions.c
	    gcc -g -c functions.c
clean:
	rm *.o
	rm tp2
