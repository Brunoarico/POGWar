CFLAGS  = -g -Wall -Wno-unused-result -ansi -O2 -pedantic
T=0.0001
F=testes/orbital.txt

default:
	$(CC) $(CFLAGS) -c *.c *.h
	$(RM) *.gch
	$(CC) $(CFLAGS) *.o -o ./testes/tmp/tmp

teste_orbita:
	make default
	./testes/tmp/tmp $(T) -k -k < $(F) | python testes/teste.py

teste_orbita2:
	make default
	./testes/tmp/tmp $(T) < $(F)



