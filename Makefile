# Utilizado para gerar nosso executável.
CFLAGS  = -g -Wall -Wno-unused-result -O0 -pedantic
T=0.0001
F=testes_simulacao/orbital.txt

ifeq ($(shell uname),Linux)
    GLFWFLAGS = -lm -lglfw3 -lGL -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXcursor -lXinerama
else
    GLFWFLAGS = -lglfw3 -framework OpenGL
endif

default: image.o physics.o vector.o moviments.o shape.o object.o draw.o vertices.o bsp.o jogo.o 
	$(CC) $(CFLAGS) *.o -o jogo -lm $(GLFWFLAGS) -lpng16

jogo.o: jogo.c
	$(CC) $(CFLAGS) -ansi -c  *.c 

image.o: libs/graphs/image.c libs/graphs/image.h
	$(CC) $(CFLAGS) -ansi -c $^

physics.o: libs/physics/*.c libs/physics/*.h
	$(CC) $(CFLAGS) -ansi -c $^

vector.o: libs/math/vector.c libs/math/vector.h
	$(CC) $(CFLAGS) -ansi -c $^

moviments.o: libs/simulation/moviments.c libs/simulation/moviments.h
	$(CC) $(CFLAGS) -ansi -c $^

barnes_hut.o: libs/simulation/barnes_hut.c libs/simulation/barnes_hut.h
	$(CC) $(CFLAGS) -ansi -c $^

bsp.o: libs/simulation/bsp.c libs/simulation/bsp.h
	$(CC) $(CFLAGS) -ansi -c $^

vertices.o: libs/simulation/vertices.c libs/simulation/vertices.h
	$(CC) $(CFLAGS) -ansi -c $^

shape.o: libs/graphs/shape.c libs/graphs/shape.h
	$(CC) $(CFLAGS) -ansi -c $^

draw.o: libs/graphs/draw.c libs/graphs/draw.h
	$(CC) $(CFLAGS) -ansi -c $^

object.o: libs/engine/object.c libs/engine/object.h
	$(CC) $(CFLAGS) -ansi -c $^

draw.o: libs/graphs/bitmap.c libs/graphs/bitmap.h
	$(CC) $(CFLAGS) -ansi -c $^

build: config.h
	make clean
	make

#bitmap.o: libs/graphs/bitmap.c libs/graphs/bitmap.h
#	$(CC) $(CFLAGS) -ansi -c libs/graphs/bitmap.c libs/graphs/bitmap.h
.PHONY: build clean teste teste_orbita all

all:
	echo $(targets)

teste_orbita:
	make default
	./jogo $(T) -k -k < $(F) | python testes_simulacao/plot.py

teste:
	./jogo $(T) < $(F)

tar:
	make clean
	COPYFILE_DISABLE=1 tar -cvf parte_2.tar ./*

clean:
	$(RM) jogo
	$(RM) *.o
	find . -name "*.gch" -exec $(RM) -rf {} \;
	find . -name "*~" -exec $(RM) -rf {} \;
