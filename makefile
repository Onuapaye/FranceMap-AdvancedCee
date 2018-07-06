all: LectSix
LectSix: City.o List.o status.o
	gcc City.o List.o status.o -o LectSix
City.o: City.c
	gcc -c City.c
List.o: List.c
	gcc -c List.c
status.o: status.c
	gcc -c status.c
clean:
	rm -rf *o LectSix

#DEPENDENCIES: don't remove this line