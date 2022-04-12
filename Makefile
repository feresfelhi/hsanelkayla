prog:main.o fonctionperso.o score.o 
	gcc main.o fonctionperso.o score.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
main.o:main.c 
	gcc -c main.c -g
fonctionperso.o:fonctionperso.c
	gcc -c fonctionperso.c -g 
score.o:score.c
	gcc -c score.c -g

