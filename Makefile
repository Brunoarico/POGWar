default:
	gcc *.c *.h -lm -lglut -lGL -lGLU -g -o jogo && xargs < simulacao.txt  ./jogo
