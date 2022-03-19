prog:minimap.o main.o 
	gcc minimap.o main.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
picture.o:minimap.c
	gcc -c minimap.c -g
