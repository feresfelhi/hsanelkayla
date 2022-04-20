prog:fct.o main.o enigme.o fctBG.o fonctionperso.o score.o minimap.o
	gcc minimap.o fct.o enigme.o fctBG.o fonctionperso.o score.o main.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
fct.o:fct.c
	gcc -c fct.c -g
fctBG.o:fctBG.c
	gcc -c fctBG.c -g
enigme.o:enigme.c
	gcc -c enigme.c -g
fonctionperso.o:fonctionperso.c
	gcc -c fonctionperso.c -g 

minimap.o:minimap.c
	gcc -c minimap.c -g