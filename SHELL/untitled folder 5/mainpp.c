//
//  mainpp.c
//  
//
//  Created by Ivan on 26.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "syn.h"
//#include "tree.h"
#include "exec.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

jmp_buf ebuf;


void gotonew(int smsm)
{
    longjmp(ebuf, 3);
}

int main()//perreor ; защита
{
    //int i;
    char ** main_list = NULL;
    signal(SIGINT, gotonew);
    tree result_tree = NULL;
    int i = 4;
    while (!feof(stdin))
    {
        printf("Input$ \n");
        main_list = syn();
        if(main_list != NULL && strcmp(*main_list,"\n\0") && strcmp(*main_list,"\0"))
        {
            if (main_list && strcmp(*main_list,"\n\0"))
                result_tree = build_tree(main_list);
            if(result_tree != NULL)
            {
                if (result_tree)
                execute(result_tree);
                //printf("\n__DEBUG_1___\n");
                i = setjmp(ebuf);
                //printf("\n__DEBUG_2___\n");
                if (result_tree != NULL)
                    delete_tree(result_tree);
                if (main_list != NULL)
                    clearlist();
                result_tree = NULL;
                main_list = NULL;
            }
        }
    }
}
