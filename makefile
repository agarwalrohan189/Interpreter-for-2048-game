all: game

game: main.cpp lex.yy.c parse.tab.c parse.tab.h Board.o Tiles.o
	g++ -std=c++11 -o game main.cpp Board.o Tiles.o parse.tab.c lex.yy.c -DYYDEBUG=1 -Wno-deprecated-register -Wno-deprecated

parse.tab.c parse.tab.h: parse.y
	bison -t -v -d parse.y 

lex.yy.c: scan.flex parse.tab.h
	flex scan.flex 

Tiles.o: Tiles.cpp 2048.h
	g++ -std=c++11 -c Tiles.cpp

Board.o: Board.cpp 2048.h
	g++ -std=c++11 -c Board.cpp 

clean:
	rm game parse.tab.c lex.yy.c parse.tab.h Board.o Tiles.o parse.output