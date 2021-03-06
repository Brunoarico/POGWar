# Utilizado para gerar nosso executável.
CFLAGS  = -g -Wall -Wno-unused-result -O3 -pedantic

ifeq ($(shell uname),Linux)
    GLFWFLAGS = -lm -lglfw3 -lGL -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXcursor -lXinerama
else
    GLFWFLAGS = -lglfw3 -framework OpenGL
endif

default: image.o physics.o vector.o moviments.o shape.o object.o draw.o bitmap.o vertices.o bsp.o controls.o jogo.o 
	$(CC) $(CFLAGS) *.o -o jogo $(GLFWFLAGS)  -lpng

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

controls.o: libs/engine/controls.c libs/engine/controls.h
	$(CC) $(CFLAGS) -ansi -c $^

bitmap.o: libs/graphs/bitmap.c libs/graphs/bitmap.h
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
	COPYFILE_DISABLE=1 tar -cvf parte_4.tar ./*

zip:
	@ make clean > /dev/null
	@ zip -r tmp.zip ./* > /dev/null
	#md5 -q tmp.zip | awk '{print $1".zip"}' | xargs mv tmp.zip

clean:
	$(RM) jogo
	$(RM) *.o
	find . -name "*.gch" -exec $(RM) -rf {} \;
	find . -name "*~" -exec $(RM) -rf {} \;
