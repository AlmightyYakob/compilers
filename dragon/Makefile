CC = gcc
FLAGS = -g
YACC = yacc
LEX = lex

mypc: y.tab.o lex.yy.o
	$(CC) $(FLAGS) -o mypc y.tab.o lex.yy.o -ll -ly

y.tab.o: y.tab.c
	$(CC) $(FLAGS) -c y.tab.c

lex.yy.o: lex.yy.c
	$(CC) $(FLAGS) -c lex.yy.c

y.tab.c: pc.y
	$(YACC) -y -dv pc.y

lex.yy.c: pc.l
	$(LEX) -l pc.l

clean:
	rm -f mypc *.o y.tab.* lex.yy.*