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


int main()
{
    char ** main_list = NULL;
    tree result_tree;
    int i = 4;
    while (i--)
    {
        printf("Input$ \n");
        main_list = syn();
        
        if (main_list)
        result_tree = build_tree(main_list);
        
        if (result_tree)
        execute(result_tree);
        
        dup2(1,1);
        dup2(0,0);
        
        main_list = NULL;
        result_tree = NULL;

        clearlist();
    }
    
}
