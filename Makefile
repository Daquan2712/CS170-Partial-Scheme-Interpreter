#To run, put this file together with lexer.h, and lexer.c
#in the same directory. Run "make". Then the executable
#is "schemer," which just takes a line of input and
#breaks it up into tokens.


scheme: main.o parser.o lexer.o evaluate.o
	gcc -o scheme main.o parser.o lexer.o evaluate.o
	
parser.o: parser.c
	gcc -c parser.c

lexer.o: lexer.c
	gcc -c lexer.c

main.o: main.c
	gcc -c main.c

evaluate.o: evaluate.c
	gcc -c evaluate.c

clean:
	rm -f *~ *.o *.a

#^^^^^^This space must be a TAB!!.



