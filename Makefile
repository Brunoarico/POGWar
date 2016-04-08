# Utilizado para gerar nosso executável.
CFLAGS  = -g -Wall -Wno-unused-result -O2 -pedantic
T=0.0001
F=testes_simulacao/orbital.txt

default: physics.o vector.o moviments.o jogo.o 
	$(CC) $(CFLAGS) -lglfw3 -framework OpenGL *.o -o jogo -lm

jogo.o: jogo.c
	$(CC) $(CFLAGS) -ansi -c  -lglfw3 -framework OpenGL *.c 

physics.o: libs/physics/*.c libs/physics/*.h
	$(CC) $(CFLAGS) -ansi -c libs/physics/*.c libs/physics/*.h

vector.o: libs/math/vector.c libs/math/vector.h
	$(CC) $(CFLAGS) -ansi -c libs/math/vector.c libs/math/vector.h

moviments.o: libs/simulation/moviments.c libs/simulation/moviments.h
	$(CC) $(CFLAGS) -ansi -c libs/simulation/moviments.c libs/simulation/moviments.h

teste_orbita:
	make default
	./jogo $(T) -k -k < $(F) | python testes_simulacao/plot.py

teste:
	./jogo $(T) < $(F)

build:
	make default
	COPYFILE_DISABLE=1 tar -cvf parte_1.tar ./testes_simulacao *.c *.h Makefile

clean:
	$(RM) *.gch
	$(RM) *.o
