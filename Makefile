prog:fct.o main.o enigme.o enigmeImg.o fctBG.o fonctionperso.o score.o minimap.o enemi.o blanc.o
	gcc minimap.o fct.o enigmeImg.o enigme.o fctBG.o enemi.o fonctionperso.o score.o blanc.o main.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
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
enemi.o:enemi.c
	gcc -c enemi.c -g
enigmeImg.o:enigmeImg.c
	gcc -c enigmeImg.c -g
score.o:score.c
	gcc -c score.c -g
blanc.o:blanc.c
	gcc -c blanc.c -g
clean:
	rm -fr prog
execute:
	./prog
