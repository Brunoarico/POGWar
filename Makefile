default:
	gcc *.c *.h -lm -g -o jogo && xargs < simulacao.txt  ./jogo
