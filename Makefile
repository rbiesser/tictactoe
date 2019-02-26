all: tictactoe.exe

tictactoe.exe:
	gcc tictactoe.c -o tictactoe.exe

clean:
	rm -f tictactoe.exe
