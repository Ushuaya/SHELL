all: mainpp syn hh dd 
	gcc -o ready.o mainpp.o syn.o tree.o exec.o


mainpp: mainpp.c
	gcc -Wall -c mainpp.c
syn: syn.c
	gcc -Wall -c syn.c
hh: tree.c
	gcc -Wall -c tree.c
dd: exec.c
	gcc -Wall -c exec.c

