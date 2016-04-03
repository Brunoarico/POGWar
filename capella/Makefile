CFLAGS  = -g -Wall -Wno-unused-result -ansi -O2 -pedantic

default:
	$(CC) $(CFLAGS) -c *.c *.h
	$(RM) *.gch
	$(CC) $(CFLAGS) *.o -o tmp

orbita:
	make default
	echo "-------"
	./tmp 0.0000001 < testes/orbital.txt  > test.txt & python testes/teste.py &


