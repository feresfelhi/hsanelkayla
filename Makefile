prog:enigme.o main.o
	gcc enigmeImg.o main.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
enigme.o:enigmeImg.c
	gcc -c enigmeImg.c -g
