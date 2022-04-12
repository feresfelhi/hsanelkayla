prog:main.o fonctionperso.o vieetscore.o 
	gcc main.o fonctionperso.o vieetscore.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
main.o:main.c 
	gcc -c main.c -g
fonctionperso.o:fonctionperso.c
	gcc -c fonctionperso.c -g 
vieetscore.o:vieetscore.c
	gcc -c vieetscore.c -g

