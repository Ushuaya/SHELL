This is SHELL

To run:
	1) Open directory with program in terminal
	2) Write "make" , then press ENTER
	3) Write "./ready.o" , then press ENTER
	4) Input your tests after string Input$
	5) To stop press ctrl-d

Available syntax:
<cmd>
<cmd> < <file>
<cmd> > <file>
<cmd> >> <file>
<cmd>&
<cmd>|<cmd>|<cmd>|<cmd>| ... |<cmd>
<cmd>|<cmd>|<cmd>|<cmd>| ... |<cmd>&
<cmd>;<cmd>

P.S.
You also can try combinations of this syntax
<cmd> means command and maybe parameters 




On development:
&&
||

But simple tests like 
pwd&&pwd&&pwd&&___&&pwd
pwd||pw||pwd||pwd
pwd||pw&&pwd
pwd||p||wp&&pwd&&pwd||pwd
pwd&&pwd||pwd
pwd||pwd&&pwd

are working





Tests, on which you can estimate this SHELL:

 cd ..
 pwd
 echo homedir: $HOME
 cd 
 pwd > fpwd
 who >> fpwd
 cat < file.in > file.out
 cat < file.in >> file.out
 zcat < file.tar.gz | tar -xv
 yes | yes | yes | yes | yes | yes | yes | yes | head
 cat < /dev/null | head | head | head | head | head
 pwd > current_dir.txt
 ls | cat | cat | cat | cat
 yes | yes | yes | yes | sleep 10 | pwd
 cat | sort –r | cat –n
 sleep 10; pwd
 sleep 5 &