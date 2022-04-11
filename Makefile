prog:fctBG.o main.o
	gcc fctBG.o main.o -o prog -g -lSDL -lSDL_image
main.o:main.c
	gcc -c main.c -g
fctBG.o:fctBG.c
	gcc -c fctBG.c -g
