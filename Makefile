<<<<<<< HEAD
prog:fct.o fctBG.o main.o
	gcc fct.o fctBG.o main.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
=======
prog:fct.o main.o enigme.o
	gcc fct.o enigme.o main.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
>>>>>>> 0abcd783484d0837f3cdb618df5e1ba86e229710
main.o:main.c
	gcc -c main.c -g
fct.o:fct.c
	gcc -c fct.c -g
<<<<<<< HEAD
fctBG.o:fctBG.c
	gcc -c fctBG.c -g
=======
enigme.o:enigme.c
	gcc -c enigme.c -g

>>>>>>> 0abcd783484d0837f3cdb618df5e1ba86e229710
