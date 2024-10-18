default: clean
	clear
	flex lexer.l
	bison -dv parser.y
	gcc -o parser parser.tab.c lex.yy.c analizator_sem.c generator_assembly.c -lfl

clean:
	rm -f parser parser.tab.c parser.tab.h parser.output lex.yy.cS
