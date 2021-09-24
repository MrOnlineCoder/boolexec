CC=g++
CFLAGS=-std=c++11 -g -O2 -c -Iinclude
OBJS=obj/Lexer.o obj/Main.o  obj/AST.o obj/Parser.o obj/Runtime.o obj/Tuple.o

obj/Lexer.o: src/Lexer.cpp
	$(CC) $(CFLAGS) -o obj/Lexer.o src/Lexer.cpp

obj/Main.o: src/Main.cpp
	$(CC) $(CFLAGS) -o obj/Main.o src/Main.cpp 

obj/AST.o: src/AST.cpp
	$(CC) $(CFLAGS) -o obj/AST.o src/AST.cpp 

obj/Parser.o: src/Parser.cpp
	$(CC) $(CFLAGS) -o obj/Parser.o src/Parser.cpp 

obj/Runtime.o: src/Runtime.cpp
	$(CC) $(CFLAGS) -o obj/Runtime.o src/Runtime.cpp 

obj/Tuple.o: src/Tuple.cpp
	$(CC) $(CFLAGS) -o obj/Tuple.o src/Tuple.cpp 

run: $(OBJS)
	$(CC)  $(OBJS) -g -o boolexec
	./boolexec