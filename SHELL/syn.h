
#define EOF (-1)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
//#include <signal.h>
#include <math.h>



//char ** list;

char** syn(void);
void clearlist(void);
void null_list(void);
int termlist(void);
void nullbuf(void);
int addsym(void);
int addword(void);
void printlist(void);
int Check_of_strange_sym(int c);
char getsym(void);
void sortlist(void);
//void syntaxx(void);



