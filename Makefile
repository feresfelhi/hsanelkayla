prog:BG.o main.o
	gcc BG.o main.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
BG.o:BG.c
	gcc -c BG.c -g