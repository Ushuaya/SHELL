//
//  exec.c
//  
//
//  Created by Ivan on 07.12.2020.
//

#include "exec.h"

void thmsng()
    {
        
        signal(SIGINT, SIG_IGN);
    }


int execute(tree run_tree)
{
    tree tmp_tree = run_tree;
    //printf ("%s\n", *(run_tree->argv));
    
    //signal(SIGINT, SIG_IGN);
    int LOGICAL_VALUE = 0;
    int OR_LOGICAL_VALUE = 0;
    int AND_LOGICAL_VALUE = 1;
    int COMMON_LOGICAL_VALUE = 1;
    int file;
    int iteration = 0;
    int Status;
    
    while(run_tree)
    {
        if (run_tree->argv)
        {
            int pid1;
            
            if (run_tree->infile)
            {
                file = open(run_tree->infile, O_RDONLY);
                if (file == -1)
                {
                    printf("Open file error\n");
                    goto error;
                }
                dup2(file, 0);
                close(file);
            }
            
            if (run_tree->outfile != NULL)
            {
                if (run_tree->append)
                    {
                        file = open(run_tree->outfile, O_WRONLY|O_APPEND);
                        if (file == -1)
                        {
                            printf("Open file error\n");
                            goto  error;
                        }
                        dup2 (file, 1);
                        close (file);
                    }
                else
                    {
                    file = open(run_tree->outfile, O_WRONLY|O_CREAT );
                        if (file == -1)
                        {
                            printf("Open file error\n");
                            goto  error;
                        }
                    dup2 (file, 1);
                    close (file);
                    }
            }
            
            //son
            printf("ORLV: %d\n", OR_LOGICAL_VALUE);
            if ((pid1 = fork()) == 0)
            {
                if (run_tree->type != NXT)//CASE OF LOGICAL EXPRESSION
                {
                    if(!((OR_LOGICAL_VALUE == 1 && run_tree->type != AND)
                         || (run_tree->type == AND && AND_LOGICAL_VALUE == 0)))
                    {
                        if(execvp((run_tree->argv)[0], run_tree->argv) == -1)
                        {
                            printf("Exec Error\n");
                            //error
                            exit(1);
                        }
                        else
                        {
                            exit(0);
                        }
                    }
                    else
                    {
                        exit(0);
                    }
                }
                else//NO LOGICalS
                {
                    if(execvp((run_tree->argv)[0], run_tree->argv) == -1)
                    {
                        printf("Exec Error\n");
                        //error
                        exit(1);
                    }
                    else
                    {
                        exit(0);
                    }
                }
            }
            if(run_tree->backgrnd == 0)
            {
                signal(SIGINT, SIG_IGN);
                wait(&Status);
                signal(SIGINT, SIG_DFL);
                if(WIFEXITED(Status) && WEXITSTATUS(Status) == 0)
                {
                    LOGICAL_VALUE = 1;
                }
                else
                {
                    LOGICAL_VALUE = 0;
                }
            }
            rewind(stdin);
            rewind(stdout);

            printf("wait nu;;\n");
            
            //father
            if(run_tree->type != NXT)
            {
                if ((LOGICAL_VALUE == 0) && (run_tree->type == AND))
                {
                    if(OR_LOGICAL_VALUE != 1)
                    {
                        AND_LOGICAL_VALUE = 0;
                    }
                    OR_LOGICAL_VALUE = 0;
                }
                printf("LV: %d\n", LOGICAL_VALUE);
                if ((LOGICAL_VALUE == 1) && (run_tree->type == OR))
                {
                    OR_LOGICAL_VALUE = 1;
                    AND_LOGICAL_VALUE = 1;
                }
            }
            
            
            
            
            
    
        }
        else
        {
            printf("Exec Error\n");
            //error
        }
        
        iteration++;
        run_tree = run_tree->next;
    }
error:
end:
    printf("Execution :3\n");
    return 0;
}
