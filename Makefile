CFLAGS  = -g -Wall -Wno-unused-result -O2 -pedantic
T=0.0001
F=testes_simulacao/orbital.txt

default:
	$(CC) $(CFLAGS) -ansi -c *.c *.h
	$(CC) $(CFLAGS) *.o -o tmp -lm

teste_orbita:
	make default
	./tmp $(T) -k -k < $(F) | python testes_simulacao/plot.py

teste_orbita2:
	make default
	./tmp $(T) < $(F)

build:
	COPYFILE_DISABLE=1 tar -cvf parte_1.tar ./testes_simulacao *.c *.h Makefile
