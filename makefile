prog:main.o enemi.o 
	gcc main.o enemi.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
main.o:main.c
	    gcc -c main.c -g
enemi.o:enemi.c
	    gcc -c enemi.c -g
