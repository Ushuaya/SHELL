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
long Check;
int check_func = 0;
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
char * tmp_buf = NULL;
char ** tmp_list = NULL;




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

int termlist(void)//Placing the NULL symbol in the end of list
{
    if (list==NULL) return 0;
    if (current_list_index>size_of_list - 1)
    {
        tmp_list = list;
        if ((tmp_list = realloc(tmp_list,(size_of_list + 1) * sizeof(*list))) == NULL)
        {
            fprintf(stderr, "\n$$ realloc error &&\n");
            //
            return -1;
        }
        list = tmp_list;
        //free ( tmp);
    }
    list[current_list_index]=NULL;
    
    //char ** tmp = list;
    tmp_list = list;
    if ((tmp_list=realloc(tmp_list,(size_of_list = current_list_index+1) * sizeof(*list))) == NULL)
    {
        fprintf(stderr, "\n$$ realloc error &&\n");
        //free (tmp);

        return -1;
        
    }
    list = tmp_list;
    //free (tmp);
    return 0;
}

void nullbuf(void)//NULLing buf
{
    buf=NULL;
    size_of_buf=0;
    current_buf_index=0;
}

int addsym(void)
{
    //printf("\nDEBUG__REALLOC\n");
    //realloc(tmp, size_of_buf);
    //printf("\nDEBUG_2_REALLOC\n");
    tmp_buf = buf;
    if (current_buf_index>size_of_buf - 1)
    {
        //printf("\nDEBUG_4_REALLOC\n");

        if ((tmp_buf = realloc(tmp_buf, ++size_of_buf)) == NULL) //if current index bigger than the buf size
        {
            fprintf(stderr, "\n$$ realloc error &&\n");
            //free (buf);
            //free (tmp_buf);
            return -1;
        }
        //buf = realloc(buf, ++size_of_buf);
        //printf("\nDEBUG_3_REALLOC\n");
        //buf = (realloc(buf, ++size_of_buf));
        buf = tmp_buf;
        //free(tmp);
    }
    //printf("\nDEBUG_5_REALLOC\n");

    buf[current_buf_index++] = c;
    return 0;
}

int addword(void)
{
    if (current_buf_index>=size_of_buf)
    {
        tmp_buf = buf;
        if ((tmp_buf = realloc(tmp_buf, size_of_buf += 1)) == NULL) // To use strings we have to have symbol /0 in the end of the string
        {
            fprintf(stderr, "\n$$ realloc error &&\n");
            //free(tmp);
            return -1;
        }
        buf = tmp_buf;
       // free(tmp);
    }
    buf[current_buf_index++] = '\0';

    
    tmp_buf = buf;
    if ((tmp_buf = realloc(tmp_buf,size_of_buf = current_buf_index)) == NULL)//In case if the size of word is smaller than buf size
    {
        fprintf(stderr, "\n$$ realloc error &&\n");
        //free(tmp);
        return -1;
    }
    buf = tmp_buf;
    //free(tmp);
    if (current_list_index>size_of_list - 1)//if current list bigger than its' size
    {
        tmp_list = list;
        if((tmp_list = realloc(tmp_list, (size_of_list += 1) * sizeof(*list))) == NULL)
        {
            fprintf(stderr, "\n$$ realloc error &&\n");
            //free(tmp);
            return -1;
        }
        list = tmp_list;
        //free(tmp);
    }
    list[current_list_index++] = buf;
    return 0;
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
        if ((Check = fread(str, sizeof(char), str_size, stdin)) != str_size)
        {
            fprintf(stderr, "\n$$ fread error &&\n");

        }

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
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
                //printf("Your list is:  ");
                //printlist();
                //sortlist();
                //printf("Your sorted list is:");
                //printlist();
                if ((check_func = termlist()) == -1) //Nulling list
                {
                    goto error;
                }
                //clearlist();// clearing memory
                nullbuf();
                inputing_to_str = 0;//we need to NULL it because when we will input it the str must have zero index on it
                goto FINITO;
            }

            while (c == '\t')
            {
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
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
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                /* Greater: */
                if (c != '>')
                {
                    if ((check_func = addword()) == -1)
                    {
                        goto error;
                    }
                    nullbuf();
                    continue;
                }
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                /* Greater2: */
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
                nullbuf();
                continue;
            }

            if(c == ';')
            {
                nullbuf();
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                /* Greater2: */
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
                nullbuf();
                continue;
            }
        
            if(c == '<')
            {
                nullbuf();
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                /* Greater2: */
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
                nullbuf();
                continue;
            }
        
            if(c == '(')
            {
                nullbuf();
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
            
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
                nullbuf();
                continue;
            }
        
            if(c == ')')
            {
                nullbuf();
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
                nullbuf();
                continue;
            }

            if(c == '&')
            {
                nullbuf();
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                
                if (c != '&')
                {
                    if ((check_func = addword()) == -1)
                    {
                        goto error;
                    }
                    nullbuf();
                    continue;
                }
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
                nullbuf();
                continue;
            }
        
            if(c == '|')
            {
                nullbuf();
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                
                if (c != '|')
                {
                    if ((check_func = addword()) == -1)
                    {
                        goto error;
                    }
                    nullbuf();
                    continue;
                }
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
                nullbuf();
                continue;
            }
        
            
        //printf ("\ns: %c\n", c);

            while (Check_of_strange_sym(c))//only symbols
            {
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
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
                    if ((check_func = addsym()) == -1)
                    {
                        goto error;
                    }
                    c = getsym();
                }
                c = getsym();
                //addword();
                //nullbuf();
                if (!Check_of_strange_sym(c) && c != '\\' && c != '"')
                {
                    if ((check_func = addword()) == -1)
                    {
                        goto error;
                    }
                    nullbuf();
                }
                if (c != ' ' )
                    continue;
            }
        
        
        
            if (c == '\\')
            {
                //printf ("\nsym1: %c\n", c);
                c = getsym();
                if ((check_func = addsym()) == -1)
                {
                    goto error;
                }
                c = getsym();
                if (!Check_of_strange_sym(c) && c != '\\' && c != '"')
                {
                    if ((check_func = addword()) == -1)
                    {
                        goto error;
                    }
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
                        if ((check_func = addsym()) == -1)
                        {
                            goto error;
                        }
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
                        if ((check_func = addword()) == -1)
                        {
                            goto error;
                        }
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
                        if ((check_func = addsym()) == -1)
                        {
                            goto error;
                        }
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
                        if ((check_func = addword()) == -1)
                        {
                            goto error;
                        }
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
                        if ((check_func = addsym()) == -1)
                        {
                            goto error;
                        }
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
                        if ((check_func = addword()) == -1)
                        {
                            goto error;
                        }
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
                        if ((check_func = addsym()) == -1)
                        {
                            goto error;
                        }
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
                        if ((check_func = addword()) == -1)
                        {
                            goto error;
                        }
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
                if ((check_func = addword()) == -1)
                {
                    goto error;
                }
            nullbuf();
            //printlist();
        
    }
    i = setjmp(ebuf);

    //printf("\n_DBG__\n");
    goto FINITO;
error:

    termlist();
    clearlist();
    free(list);
    free(buf);
    
    int ind;
    size_of_list=0;
    current_list_index=0;
    if (tmp_list != NULL)
    {
        for (ind = 0; tmp_list[ind] != NULL; ind++)
            free(tmp_list[ind]);
        free(tmp_list);
        tmp_list=NULL;
    }

    free(tmp_buf);
FINITO:
    
    return list;
    }
