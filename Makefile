prog:fct.o main.o
	gcc fct.o main.o -o prog -g -lSDL -lSDL_image
main.o:main.c
	gcc -c main.c -g
fct.o:fct.c
	gcc -c fct.c -g
