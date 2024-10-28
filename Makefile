CC = gcc
LEX = flex
BISON = bison
CFLAGS = -Wall -g

TARGET = parser

default: clean
	clear
	$(LEX) lexer.l
	$(BISON) -dv parser.y
	$(CC) -o $(TARGET) parser.tab.c lex.yy.c analizator_sem.c generator_assembly.c -lfl

clean:
	rm -f $(TARGET) parser.tab.c parser.tab.h parser.output lex.yy.c
