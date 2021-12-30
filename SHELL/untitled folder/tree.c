//
//  tree.c
//  
//
//  Created by Ivan on 28.11.2020.
//














#include "tree.h"
tree begin_cmd; /* начальная команда, лучше назвать ее beg_cmd, это локальная переменная
 функции build_tree()*/
tree current_cmd; /* текущая команда, лучше назвать ее cur_cmd, локальная переменная функции
 build_tree()*/
tree previous_cmd;
tree make_backgrnd_cmd;//For saving part of sequence to make backgrnd = 1 in it
tree tmp_tree;
tree tmp_tree_save;

int sizeofword(char * x)
{
    int i = 0;
    while (x[i] != 0)
    {
        i++;
    }
    return i;
}

enum type_of_graph what_is_this_arg(char * f_word)
{
    if ((f_word == NULL) || (*f_word == '\0'))
    {
        return NULL_CMD;
    }
    else
    {
        if (f_word[0] != '>'  &&  f_word[0] != '|' && f_word[0] != '&' && f_word[0] != ';' && f_word[0] != '<')
        {
            return CONV;
        }
        else
        {
            if (f_word[0] == '>')
            {
                if(sizeofword(f_word) == 1)
                {
                    return OUT;
                }
                else
                {
                    if (f_word[1] == '>')
                    {
                        return OUT_APP;
                    }
                    else
                    {
                        return CIDIOT;
                    }
                }
            }
            if (f_word[0] == '|')
            {
                if(sizeofword(f_word) == 1)
                {
                    return CONV1;
                }
                else
                {
                    if (f_word[1] == '|')
                    {
                        return OR_CMD;
                    }
                    else
                    {
                        return CIDIOT;
                    }
                }
            }
            if (f_word[0] == '<')
            {
                return IN;
            }
            if (f_word[0] == '&')
            {
                if(sizeofword(f_word) == 1)
                {
                    return BACKGRND;
                }
                else
                {
                    if (f_word[1] == '&')
                    {
                        return AND_CMD;
                    }
                    else
                    {
                        return CIDIOT;
                    }
                }
            }
            if (f_word[0] == ';')
            {
                return POINTCOMMA;
            }
            
        }
    }
    return CIDIOT;
}

tree create_null_tree(void)
{
    tree tmp_tree;
    tmp_tree = (tree) malloc (sizeof(node));
    
    tmp_tree->argv = calloc(10, sizeof(char*));
    tmp_tree->infile = NULL;
    tmp_tree->outfile = NULL;
    tmp_tree->append = 0;
    tmp_tree->backgrnd = 0;
    tmp_tree->pipe = NULL;
    tmp_tree->next = NULL;
    tmp_tree->psubcmd = NULL;
    tmp_tree->type = NXT;
    return tmp_tree;
}


//int state_part_cmd(char* f_word)

   // if(strcmp(f_word))
    
    





void make_shift(int n){
    while(n--)
        putc(' ', stderr);
}

void print_argv(char **p, int shift){
    char **q=p;
    if(p!=NULL){
        while(*p!=NULL){
             make_shift(shift);
             fprintf(stderr, "argv[%d]=%s\n",(int) (p-q), *p);
             p++;
        }
    }
}

void print_tree(tree t, int shift)
{
    // printf ("Meow2 :3\n");

    char **p;
    if(t==NULL)
        return;
    p=t->argv;
    if(p!=NULL)
        print_argv(p, shift);
    else{
        make_shift(shift);
        fprintf(stderr, "psubshell\n");
    }
    make_shift(shift);
    if(t->infile==NULL)
        fprintf(stderr, "infile=NULL\n");
    else
        fprintf(stderr, "infile=%s\n", t->infile);
    make_shift(shift);
    if(t->outfile==NULL)
        fprintf(stderr, "outfile=NULL\n");
    else
        fprintf(stderr, "outfile=%s\n", t->outfile);
    make_shift(shift);
    fprintf(stderr, "append=%d\n", t->append);
    make_shift(shift);
    fprintf(stderr, "background=%d\n", t->backgrnd);
    make_shift(shift);
    fprintf(stderr, "type=%s\n", t->type==NXT?"NXT": t->type==OR?"OR": "AND" );
    make_shift(shift);
    if(t->psubcmd==NULL)
        fprintf(stderr, "psubcmd=NULL \n");
    else{
        fprintf(stderr, "psubcmd---> \n");
        print_tree(t->psubcmd, shift+5);
    }
    make_shift(shift);
    if(t->pipe==NULL)
        fprintf(stderr, "pipe=NULL \n");
    else{
        fprintf(stderr, "pipe---> \n");
        print_tree(t->pipe, shift+5);
    }
    make_shift(shift);
    if(t->next==NULL)
        fprintf(stderr, "next=NULL \n");
    else{
        fprintf(stderr, "next---> \n");
        print_tree(t->next, shift+5);
    }
}

tree build_tree(char ** list)
{
    
    //printf ("Meow :3\n");
    
    
    enum type_of_graph our_state;
    //starting
    our_state = BEGIN;
    
    //counter for the interal argv in the specific node
    int j = 0;
    //counter for the word in the our external list
    int i = 0;
    char* tmp_word;
    while (1)
    {
        switch (our_state)
        {
            case BEGIN:
                //Creating of NULL node
                //If our list is not empty
                if (what_is_this_arg(list[0]) == NULL_CMD)
                {
                    printf("THERE IS NO LIST\n");
                    our_state = END;
                    break;
                }
                current_cmd = create_null_tree();
                //saving of root
                begin_cmd = current_cmd;
                
                //this tree node is made in order to
                //control the part of the tree
                //needed to be defined with
                //backgrnd = 1 in the conveyor
                //because this value have to be
                //set only in the conveyor,
                //bouded to the "&", but
                //if we have smthg like
                //cmd1|cmd2;cmd3&
                //backgrnd value wont be
                //set in cmd1 and cmd2
                make_backgrnd_cmd = current_cmd;
                
                //Inserting info of element
                if (list != NULL)
                {
                       
                    if (list[i+1] != NULL)
                    {
                        if ((our_state = what_is_this_arg(list[i])) == CONV)
                        {
                            current_cmd->argv[j] = list[i];
                        }
                        else
                        {
                            j = 0;
                            break;
                        }
                        i++; j++;
                    }
                    else
                    {
                        our_state = END;
                        break;
                    }
                    //case of CONV is here
                    break;
                }
                else
                {
                    our_state = END;
                    break;
                }
                
            case CONV:
                if (list != NULL)
                {
                       
                    if (list[i+1] != NULL)
                    {
                        if ((our_state = what_is_this_arg(list[i])) == CONV)
                        {
                            current_cmd->argv[j] = list[i];
                        }
                        else
                        {
                            //throgh the brake we are going to
                            //the next operation
                            j = 0;
                            break;
                        }
                        i++; j++;
                    }
                    else
                    {
                        our_state = END;
                        break;
                    }
                    //case of CONV is here
                    break;
                }
                else
                {
                    //if the list is ended
                    our_state = END;
                    break;
                }
                
            case CONV1:
                //previous_cmd->type = NXT;
                                
                //current_cmd->pipe = tmp_tree;
                tmp_tree = create_null_tree();
                tmp_tree_save = tmp_tree;
                i++;
                if((our_state = what_is_this_arg(list[i])) != CONV)
                {
                    //if there is no command after |
                    //free(tmp_tree);
                    printf("Expected name of command \"<cmd> | <NULL>\"\n");
                    our_state = CIDIOT;
                    goto ERROR_GO;
                }
                tmp_tree->argv[0] = list[i];
                i++;
                while((our_state = what_is_this_arg(list[i])) == CONV1)
                {
                    i++;
                    
                    if((our_state = what_is_this_arg(list[i])) != CONV)
                    {
                        //if there is no command after |
                        free(tmp_tree);
                        printf("Expected name of command \"<cmd> | <NULL>\"\n");
                        our_state = CIDIOT;
                        goto ERROR_GO;
                    }
                    tmp_tree->pipe = create_null_tree();
                    tmp_tree->pipe->argv[0] = list[i];
                    tmp_tree = tmp_tree->pipe;
                    i++;
                }
                //print_tree(tmp_tree_save, 10);
                current_cmd->pipe = tmp_tree_save;
                //free(tmp_tree);
                //free(tmp_tree_save);
                /*
                previous_cmd = current_cmd;
                current_cmd = create_null_tree();
                previous_cmd->pipe = current_cmd;
                 */
                break;
                
            case IN:
                i++;
                if((our_state = what_is_this_arg(list[i])) != CONV)
                {
                    //if there is no command after <
                    printf("Expected name of file \"<cmd> < <NULL>\"\n");
                    our_state = CIDIOT;
                    break;
                }
                current_cmd->infile = list[i];
                i++;
                our_state = what_is_this_arg(list[i]);
                break;
                
            case IN1:
                //!?!?!?!?
                break;
                
            case OUT:
                i++;
                if((our_state = what_is_this_arg(list[i])) != CONV)
                {
                    //if there is no command after >
                    printf("Expected name of file \"<cmd> > <NULL>\"\n");
                    our_state = CIDIOT;
                    break;
                }
                current_cmd->outfile = list[i];
                i++;
                our_state = what_is_this_arg(list[i]);
                break;
                
            case OUT_APP:
                i++;
                if((our_state = what_is_this_arg(list[i])) != CONV)
                {
                    //if there is no command after >>
                    printf("Expected name of file \"<cmd> >> <NULL>\"\n");
                    our_state = CIDIOT;
                    break;
                }
                current_cmd->outfile = list[i];
                current_cmd->append = 1;
                i++;
                our_state = what_is_this_arg(list[i]);
                break;
            case OUT1:
                //!?!?!? what for did I make it?!?!
                break;
            case BACKGRND:
                //ERROR?!?!?!
                our_state = END;
                tree tmp_tree;
                tmp_tree = begin_cmd;
                while (make_backgrnd_cmd != NULL)
                {
                    make_backgrnd_cmd -> backgrnd = 1;
                    make_backgrnd_cmd = make_backgrnd_cmd -> pipe;
                }
                
                break;
                
                
                
            case POINTCOMMA:
                i++;
                
                if((our_state = what_is_this_arg(list[i])) == CONV)
                {
                   
                    /*
                    tree tmp_tree;
                    tmp_tree = current_cmd;
                    while ((our_state = what_is_this_arg(list[i])) == CONV1)
                    {
                        tmp_tree->pipe = create_null_tree();
                        tmp_tree = tmp_tree->pipe;
                        
                        tmp_tree->argv = list[i];
                    }
                    */
                    
                    
                    
                    
                    
                    previous_cmd = current_cmd;
                    current_cmd = create_null_tree();
                    make_backgrnd_cmd = current_cmd;
                    previous_cmd->next = current_cmd;
                    previous_cmd->type = NXT;
                    break;
                }
                else
                {
                    if(our_state == NULL_CMD)
                    {
                        //constructions like
                        //cmd;
                        //are used to be executed
                        our_state = END;
                        break;
                    }
                    else
                    {
                        //If there are smthg like
                        //cmd;;
                        our_state = CIDIOT;
                        printf("Don't know command \";<cmd>\"\n");
                        break;
                    }
                }
            case AND_CMD:
                i++;
                
                if((our_state = what_is_this_arg(list[i])) == CONV)
                {
                    //also it works in a case like
                    //<cmd>&&<cmd>
                    previous_cmd = current_cmd;
                    current_cmd = create_null_tree();
                    make_backgrnd_cmd = current_cmd;
                    previous_cmd->next = current_cmd;
                    previous_cmd->type = AND;
                }
                else
                {
                    //if there is no command after &&
                    our_state = CIDIOT;
                    printf("Expected command \"<cmd>&&<NULL>\"\n");
                    break;
                }
                
                break;
            case OR_CMD:
                i++;
                
                if((our_state = what_is_this_arg(list[i])) == CONV)
                {
                    //also it works in a case like
                    //<cmd>||<cmd>
                    previous_cmd = current_cmd;
                    current_cmd = create_null_tree();
                    make_backgrnd_cmd = current_cmd;
                    previous_cmd->next = current_cmd;
                    previous_cmd->type = OR;
                }
                else
                {
                    //if there is no command after ||
                    our_state = CIDIOT;
                    printf("Expected command \"<cmd>||<NULL>\"\n");
                    break;
                }
                
                break;
                
                
            case NULL_CMD:
            case END:
                //If everything is OK
                //we print this tree
                //and return it to main
                print_tree (begin_cmd, 5);
                return begin_cmd;
                
            case CIDIOT:
            ERROR_GO:
                //If smthg is not ok
                printf("FATAL ERROR\nYOU HAVE BROKEN YOUR PC\n\nReloading...\nDONE!\n\n");
                return NULL;
                
            default:
                //error
                printf("FATAL ERROR\nYOU HAVE BROKEN YOUR PC\n\nReloading...\nDONE!\n\n");
                return NULL;;;;;;
                
                
        }
        
        //print_tree (current_cmd, 5);
    }
    return NULL;
}


