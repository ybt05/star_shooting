main: main.o title.o draw.o game.o pause.o gameover.o gameclear.o bullet.o save.o
	gcc -o main main.o title.o draw.o game.o pause.o gameover.o gameclear.o bullet.o save.o -lncursesw

main.o: main.c main.h
	gcc -c main.c

title.o: title.c main.h
	gcc -c title.c

draw.o: draw.c main.h
	gcc -c draw.c

game.o: game.c main.h
	gcc -c game.c

pause.o: pause.c main.h
	gcc -c pause.c

gameover.o: gameover.c main.h
	gcc -c gameover.c

gameclear.o: gameclear.c main.h
	gcc -c gameclear.c

bullet.o: bullet.c main.h
	gcc -c bullet.c

save.o: save.c main.h
	gcc -c save.c

clean:
	rm -f *.o
