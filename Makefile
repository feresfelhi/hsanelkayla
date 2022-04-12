prog:fct.o fctBG.o main.o
	gcc fct.o fctBG.o main.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
fct.o:fct.c
	gcc -c fct.c -g
fctBG.o:fctBG.c
	gcc -c fctBG.c -g
