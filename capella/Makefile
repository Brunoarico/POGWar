CFLAGS  = -g -Wall -Wno-unused-result -ansi -O2 -pedantic
T=0.0001
F=testes/orbital.txt

default:
	$(CC) $(CFLAGS) -c *.c *.h
	$(RM) *.gch
	$(CC) $(CFLAGS) *.o -o ./testes/tmp/tmp

orbita:
	make default
	echo "-------"
	./testes/tmp/tmp $(T) -k < $(F) | python testes/teste.py

orbita2:
	make default
	echo "-------"
	./testes/tmp/tmp $(T) < $(F)



