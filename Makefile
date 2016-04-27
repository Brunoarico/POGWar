# Utilizado para gerar nosso executável.
CFLAGS  = -g -Wall -Wno-unused-result -O3 -pedantic
T=0.0001
F=testes_simulacao/orbital.txt

ifeq ($(shell uname),Linux)
    GLFWFLAGS = # -lglfw3 -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXcursor -lXinerama
else
    GLFWFLAGS = -lglfw3 -framework OpenGL
endif

default: physics.o vector.o moviments.o shape.o object.o draw.o vertices.o bsp.o jogo.o 
	$(CC) $(CFLAGS) $(GLFWFLAGS) *.o -o jogo -lm

jogo.o: jogo.c
	$(CC) $(CFLAGS) -ansi -c  *.c 

physics.o: libs/physics/*.c libs/physics/*.h
	$(CC) $(CFLAGS) -ansi -c libs/physics/*.c libs/physics/*.h

vector.o: libs/math/vector.c libs/math/vector.h
	$(CC) $(CFLAGS) -ansi -c libs/math/vector.c libs/math/vector.h

moviments.o: libs/simulation/moviments.c libs/simulation/moviments.h
	$(CC) $(CFLAGS) -ansi -c libs/simulation/moviments.c libs/simulation/moviments.h

barnes_hut.o: libs/simulation/barnes_hut.c libs/simulation/barnes_hut.h
	$(CC) $(CFLAGS) -ansi -c libs/simulation/barnes_hut.c libs/simulation/barnes_hut.h

bsp.o: libs/simulation/bsp.c libs/simulation/bsp.h
	$(CC) $(CFLAGS) -ansi -c libs/simulation/bsp.c libs/simulation/bsp.h

vertices.o: libs/simulation/vertices.c libs/simulation/vertices.h
	$(CC) $(CFLAGS) -ansi -c libs/simulation/vertices.c libs/simulation/vertices.h

shape.o: libs/graphs/shape.c libs/graphs/shape.h
	$(CC) $(CFLAGS) -ansi -c libs/graphs/shape.c libs/graphs/shape.h

draw.o: libs/graphs/draw.c libs/graphs/draw.h
	$(CC) $(CFLAGS) -ansi -c libs/graphs/draw.c libs/graphs/draw.h

object.o: libs/engine/object.c libs/engine/object.h
	$(CC) $(CFLAGS) -ansi -c libs/engine/object.c libs/engine/object.h

#2Dtext.o: libs/graphs/2Dtext.c libs/graphs/2Dtext.h
#	$(CC) $(CFLAGS) -ansi -c libs/graphs/2Dtext.c libs/graphs/2Dtext.h

teste_orbita:
	make default
	./jogo $(T) -k -k < $(F) | python testes_simulacao/plot.py

teste:
	./jogo $(T) < $(F)

build:
	make default
	COPYFILE_DISABLE=1 tar -cvf parte_1.tar ./testes_simulacao *.c *.h Makefile

clean:
	$(RM) jogo
	$(RM) *.o
	find . -name "*.gch" -exec $(RM) -rf {} \;
