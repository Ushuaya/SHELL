all: mainpp syn hh dd 
	gcc -o ready.o mainpp.o syn.o tree.o exec.o


mainpp: mainpp.c
	gcc -c mainpp.c
syn: syn.c
	gcc -c syn.c
hh: tree.c
	gcc -c tree.c
dd: exec.c
	gcc -c exec.c

