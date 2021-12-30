//
//  Task 3
//
//  Created by Ivan on 23.10.2020.
//
// variable for saving first str_size symbols
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
//#include <signal.h>
#include "syn.h"
#include <stdio.h>
#include <setjmp.h>


jmp_buf ebuf;
int smthng = 0;
int c;
char ** list = NULL;
char * buf = NULL;
int size_of_buf;
int size_of_list;
int current_buf_index;
int current_list_index;
//FILE* ptrFile;
#define str_size 1
char str[str_size+1];
int inputing_to_str = 0;
void gotonews(int smsm)
{
    longjmp(ebuf, 3);
}



//void syn(void);


void clearlist(void)//Releasing unneccessary memory
{
    int i;
    size_of_list=0;
    current_list_index=0;
    if (list == NULL)
        return;
    for (i = 0; list[i] != NULL; i++)
        free(list[i]);
    free(list);
    list=NULL;
}

void null_list(void)//NULLing the list of strings
{
    size_of_list = 0;
    current_list_index = 0;
    list=NULL;
}

void termlist(void)//Placing the NULL symbol in the end of list
{
    if (list==NULL) return;
    if (current_list_index>size_of_list - 1)
        list=realloc(list,(size_of_list + 1) * sizeof(*list));

    list[current_list_index]=NULL;
    list=realloc(list,(size_of_list = current_list_index+1) * sizeof(*list));
}

void nullbuf(void)//NULLing buf
{
    buf=NULL;
    size_of_buf=0;
    current_buf_index=0;
}

void addsym(void)
{
    if (current_buf_index>size_of_buf - 1)
        buf = realloc(buf, ++size_of_buf); //if current index bigger than the buf size
    buf[current_buf_index++] = c;
}

void addword(void)
{
    if (current_buf_index>=size_of_buf)
        buf = realloc(buf, size_of_buf += 1); // To use strings we have to have symbol /0 in the end of the string
    buf[current_buf_index++] = '\0';

    buf = realloc(buf,size_of_buf=current_buf_index);//In case if the size of word is smaller than buf size
    if (current_list_index>size_of_list - 1)//if current list bigger than its' size
        list = realloc(list, (size_of_list += 1) * sizeof(*list));
    list[current_list_index++] = buf;
}

void printlist(void)
{
    int i;
    if (list == NULL) return;

    for (i = 0; i < size_of_list; i++)
        printf("%s ", list[i]);
    printf("\n");
    //printf("List %d :%s\n",i , list[i]);
}

int Check_of_strange_sym(int c)//...
{
    
    return c != '\n' && c != ' ' && c != '\t' && c != '>' && c != EOF && c != ')' && c != '(' && c != '|' && c != '&' && c != ';' && c != '<' && c != '"' && c != '\\' && c != '$' && c != '#';
}

char getsym(void)//inputing of the next symbol
{
    
    
    if ((inputing_to_str >= str_size))
    {
        inputing_to_str = 0;
        //printf("\n__DEBUG__HELLO__2__\n");
        fread(str, sizeof(char), str_size, stdin);

            return str[inputing_to_str++];

    }
    return str[inputing_to_str++];
}

void sortlist(void)//Sorting of the list by leksicografy
{
    char * tmp;
    for (int i = 0; i < size_of_list; i++)
        for (int j = 0; j < size_of_list; j++)
        {
            if (strcmp(list[i], list[j]) < 0)
            {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }

}

char** syn(void)
{
    //printf("\n__DEBUD__HELLO__\n");
    int i;
    //signal(SIGINT, gotonews);
    long Check;

    //printf ("Hello!\n");
    null_list();
    nullbuf();
    goto first;//first time going
//START:
    //build_tree(list );
first:
    rewind (stdin);
    //rewind (stdout);
    Check = fread(str, sizeof(char), str_size, stdin);
    //printf ("str: %c\n", str[0]);
    
    c = getsym();
    smthng = 1;
    
    //printf("wtf: %c\n", c);
    if(c != EOF)
    while (!feof(stdin))
    {
            //MAIN PROGRAMM:

                       
            if (c == '\n' || c == '#')
            {
                if (c == '#')
                    rewind(stdin);
                addword();
                //printf("Your list is:  ");
                //printlist();
                //sortlist();
                //printf("Your sorted list is:");
                //printlist();
                termlist(); //Nulling list
                //clearlist();// clearing memory
                nullbuf();
                inputing_to_str = 0;//we need to NULL it because when we will input it the str must have zero index on it
                goto FINITO;
            }

            while (c == '\t')
            {
                addword();
                nullbuf();
                //printlist();
                c = getsym();
            }

            while (c == ' ')
            {
                c = getsym();
            }

            if(c == '>')
            {
                nullbuf();
                addsym();
                c = getsym();
                /* Greater: */
                if (c != '>')
                {
                    addword();
                    nullbuf();
                    continue;
                }
                addsym();
                c = getsym();
                /* Greater2: */
                addword();
                nullbuf();
                continue;
            }

            if(c == ';')
            {
                nullbuf();
                addsym();
                c = getsym();
                /* Greater2: */
                addword();
                nullbuf();
                continue;
            }
        
            if(c == '<')
            {
                nullbuf();
                addsym();
                c = getsym();
                /* Greater2: */
                addword();
                nullbuf();
                continue;
            }
        
            if(c == '(')
            {
                nullbuf();
                addsym();
                c = getsym();
                /* Greater2: */
                addword();
                nullbuf();
                continue;
            }
        
            if(c == ')')
            {
                nullbuf();
                addsym();
                c = getsym();
                /* Greater2: */
                addword();
                nullbuf();
                continue;
            }

            if(c == '&')
            {
                nullbuf();
                addsym();
                c = getsym();
                /* Greater: */
                if (c != '&')
                {
                    addword();
                    nullbuf();
                    continue;
                }
                addsym();
                c = getsym();
                /* Greater2: */
                addword();
                nullbuf();
                continue;
            }
        
            if(c == '|')
            {
                nullbuf();
                addsym();
                c = getsym();
                /* Greater: */
                if (c != '|')
                {
                    addword();
                    nullbuf();
                    continue;
                }
                addsym();
                c = getsym();
                /* Greater2: */
                addword();
                nullbuf();
                continue;
            }
        
            
        //printf ("\ns: %c\n", c);

            while (Check_of_strange_sym(c))//only symbols
            {
                addsym();
                c = getsym();
                //printf("IN: %c\n", c);
            }
        
        
            if(c == '"')
            {
                //addsym();
                c = getsym();
                //printf("\nsym: %c\n", c);
                //nullbuf();
                while (c != '"')
                {
                    addsym();
                    c = getsym();
                }
                c = getsym();
                //addword();
                //nullbuf();
                if (!Check_of_strange_sym(c) && c != '\\' && c != '"')
                {
                    addword();
                    nullbuf();
                }
                if (c != ' ' )
                    continue;
            }
        
        
        
            if (c == '\\')
            {
                //printf ("\nsym1: %c\n", c);
                c = getsym();
                addsym();
                c = getsym();
                if (!Check_of_strange_sym(c) && c != '\\' && c != '"')
                {
                    addword();
                    nullbuf();
                }
                if (c != ' ')
                continue;
            }
        
            if (c == '$')
            {
                c = getsym();
                if (c == 'H')
                {
                    char *s = getenv("HOME"); /* получить параметр среды */
                       //printf("home: %s\n",s);
                    //printf("%d\n", sizeof(*s));
                    int i = 0;
                    while(s[i] != '\0')
                    {
                       // printf("%c\n", s[i]);
                        c = s[i];
                        addsym();
                        //printf("a\n");
                        //printf("%lu :: %c\n", i, s[i]);
                        i++;
                    }
                    //printf("%lu\n", i);
                    c = getsym();
                    c = getsym();
                    c = getsym();
                    c = getsym();
                    //printf("%c\n", c);
                    
                    if (!Check_of_strange_sym(c) && c != '\\' && c != '"')
                    {
                        addword();
                        nullbuf();
                    }
                    if (c != ' ')
                    continue;
                }
                
                
                if (c == 'U')
                {
                    char *s = getenv("USER"); /* получить параметр среды */
                       printf("user: %s\n",s);
                    //printf("%d\n", sizeof(*s));
                    int i = 0;
                    while(s[i] != '\0')
                    {
                       // printf("%c\n", s[i]);
                        c = s[i];
                        addsym();
                        //printf("a\n");
                        //printf("%lu :: %c\n", i, s[i]);
                        i++;
                    }
                    //printf("%lu\n", i);
                    c = getsym();
                    c = getsym();
                    c = getsym();
                    c = getsym();
                    //printf("%c\n", c);
                    if (!Check_of_strange_sym(c) && c != '\\' && c != '"')
                    {
                        addword();
                        nullbuf();
                    }
                    if (c != ' ')
                    continue;
                }
                
                if (c == 'S')
                {
                    char *s = getenv("SHELL"); /* получить параметр среды */
                       //printf("home: %s\n",s);
                    //printf("%d\n", sizeof(*s));
                    int i = 0;
                    while(s[i] != '\0')
                    {
                       // printf("%c\n", s[i]);
                        c = s[i];
                        addsym();
                        //printf("a\n");
                        //printf("%lu :: %c\n", i, s[i]);
                        i++;
                    }
                    //printf("%lu\n", i);
                    c = getsym();
                    c = getsym();
                    c = getsym();
                    c = getsym();
                    c = getsym();
                    //printf("%c\n", c);
                    
                    if (!Check_of_strange_sym(c) && c != '\\' && c != '"')
                    {
                        addword();
                        nullbuf();
                    }
                    if (c != ' ')
                    continue;
                }
                
                if (c == 'E')
                {
                    int ID = geteuid();
                    int deg = log10(ID);
                    char *p = (char*) malloc(deg + 1);
                    //itoa(ID, p, 10);
                    sprintf (p, "%d", ID);
                    p[deg+1] = '\0';
                    int i = 0;
                    while(p[i] != '\0')
                    {
                       // printf("%c\n", s[i]);
                        c = p[i];
                        addsym();
                        //printf("a\n");
                        //printf("%lu :: %c\n", i, s[i]);
                        i++;
                    }
                    c = getsym();
                    c = getsym();
                    c = getsym();
                    c = getsym();
                    if (!Check_of_strange_sym(c) && c != '\\' && c != '"')
                    {
                        addword();
                        nullbuf();
                    }
                    if (c != ' ')
                    continue;
                }
                   continue;
            }

           // if (c == '#')
            {
              //  goto ccase;
            }
            
        
            //printf ("\nsym3: \%c\n", c);
            if (c != '\\' && c != '"')
            addword();
            nullbuf();
            //printlist();
        
    }
    i = setjmp(ebuf);
FINITO:

    
    return list;
    }
