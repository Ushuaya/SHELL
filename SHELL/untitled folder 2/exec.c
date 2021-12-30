//
//  exec.c
//  
//
//  Created by Ivan on 07.12.2020.
//

#include "exec.h"
int BACK = 0;
void backgrnd_f(int num)
{
    if (BACK == 1)
    {
        
    
        pid_t pid;
        //int   status;
        while (((pid = waitpid(-1, NULL , WNOHANG)) != -1) && (pid != 0))
        {
            printf("[%d] stopped \n", pid);
            //printf("DUBUG SIGNAL\n");
        }
        //printf("DUBUG SIGNAL 2\n");
    }
}

void thmsng()
    {
        
        //signal(SIGINT, SIG_IGN);
    }


int execute(tree run_tree)
{
    tree tmp_tree = run_tree;
    //printf ("%s\n", *(run_tree->argv));
    
    signal(SIGCHLD, backgrnd_f);
    int LOGICAL_VALUE = 0;
    int OR_LOGICAL_VALUE = 0;
    int AND_LOGICAL_VALUE = 1;
    int COMMON_LOGICAL_VALUE = 1;
    int file;
    int iteration = 0;
    int Status;
    int PIDS[10] = {0};
    
    
 
        
    
    
    while(run_tree)
    {
    
            if (run_tree->argv)
            {
                if (strcmp((run_tree->argv)[0], "cd\0") == 0)
                {
                    if ((run_tree->argv)[1] != NULL)
                        chdir ( (run_tree->argv)[1] );
                    else
                        goto error;
                    run_tree = run_tree->next;
                }
                else
                {
                    if (run_tree->pipe != NULL)
                    {
                        tree begin_of_pipe = run_tree;
                        
                        int stage_pipe = 0;
                        tree tmp_tree;
                        tmp_tree = run_tree;
                        while (tmp_tree != NULL)
                        {
                            tmp_tree = tmp_tree->pipe;
                            stage_pipe++;
                        }
                        tmp_tree = run_tree;
                        //printf("%d\n", stage_pipe);
                        
                        
                        
                        int fd[2], in, out, next_in, i;
                        pipe(fd); out=fd[1]; next_in=fd[0];
                        
                        
                        if (fork()==0)
                        {
                            close(next_in);
                            dup2(out,1);
                            close(out);
                            execvp((tmp_tree->argv)[0], tmp_tree->argv);
                            exit(-1);
                        }
                        tmp_tree = tmp_tree->pipe;
                        
                        in=next_in;
                        for (i=1;i<stage_pipe-1; i++)
                        {
                            close(out);
                            pipe(fd);
                            out=fd[1];
                            next_in=fd[0];
                            if(fork()==0)
                            {
                                close(next_in);
                                dup2(in,0);
                                close(in);
                                dup2(out,1);
                                close(out);
                                //run_tree = run_tree->pipe;
                                                
                                
                                execvp((tmp_tree->argv)[0], tmp_tree->argv);
                            }
                            close(in);
                            in=next_in;
                            tmp_tree = tmp_tree->pipe;///
                        }
                        close(out);
                        if (fork() == 0)
                        {
                            //printf("%s\n", (tmp_tree->argv)[0]);
                            dup2(in,0);
                            close(in);
                            
                            
                            
                            
                            
                            
                                        
                                        if (tmp_tree->infile)
                                        {
                                            file = open(tmp_tree->infile, O_RDONLY);
                                            if (file == -1)
                                            {
                                                printf("Open file error\n");
                                                exit(1);
                                            }
                                            dup2(file, 0);
                                            close(file);
                                        }
                                        
                                        if (tmp_tree->outfile != NULL)
                                        {
                                            if (tmp_tree->append)
                                                {
                                                    file = open(tmp_tree->outfile, O_WRONLY|O_APPEND|O_CREAT, 0664);
                                                    if (file == -1)
                                                    {
                                                        printf("Open file error\n");
                                                        exit(1);
                                                    }
                                                    dup2 (file, 1);
                                                    close (file);
                                                }
                                            else
                                                {
                                                file = open(tmp_tree->outfile, O_WRONLY|O_APPEND|O_CREAT, 0664);
                                                    if (file == -1)
                                                    {
                                                        printf("Open file error\n");
                                                        exit(1);
                                                    }
                                                dup2 (file, 1);
                                                close (file);
                                                }
                                        }
                                    
                                
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            execvp((tmp_tree->argv)[0], tmp_tree->argv);
                            exit(1);
                        }
                        close(in);
                        
                        if (begin_of_pipe->backgrnd == 0)
                        {
                            for( i=1; i<stage_pipe; i++)
                                wait(NULL);
                        }
                        else
                            BACK = 1;
                            
                        stage_pipe = 0;
                        iteration++;
                        
                        run_tree = run_tree->next;
                        
                        continue;
                            
                    }
                
                
                
                    int pid1;
                    
                    if ((pid1 = fork()) == 0)
                    {
                        if (run_tree->infile)
                        {
                            file = open(run_tree->infile, O_RDONLY);
                            if (file == -1)
                            {
                                printf("Open file error\n");
                                exit(1);
                            }
                            dup2(file, 0);
                            close(file);
                        }
                        
                        if (run_tree->outfile != NULL)
                        {
                            if (run_tree->append)
                                {
                                    file = open(run_tree->outfile, O_WRONLY|O_APPEND|O_CREAT, 0664);
                                    if (file == -1)
                                    {
                                        printf("Open file error\n");
                                        exit(1);
                                    }
                                    dup2 (file, 1);
                                    close (file);
                                }
                            else
                                {
                                file = open(run_tree->outfile, O_WRONLY|O_APPEND|O_CREAT, 0664);
                                    if (file == -1)
                                    {
                                        printf("Open file error\n");
                                        exit(1);
                                    }
                                dup2 (file, 1);
                                close (file);
                                }
                        }
                    
                    //son
                        if ((run_tree->type == OR) || (run_tree->type == AND))//CASE OF LOGICAL EXPRESSION
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
                            //printf("DEBUG___ %s ___\n", (run_tree->argv)[0]);
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
                    
                    
                    
                    //father
                    
                    //signal(SIGINT, SIG_IGN);
                    waitpid(-1, &Status , WNOHANG);
                    wait(&Status);
                    //printf("DEBUG___fork()___1\n");
                    //signal(SIGINT, SIG_DFL);
                    if(WIFEXITED(Status) && WEXITSTATUS(Status) == 0)
                    {
                        LOGICAL_VALUE = 1;
                    }
                    else
                    {
                        LOGICAL_VALUE = 0;
                    }


                    if((run_tree->type == OR) || (run_tree->type == AND))
                    {
                        if ((LOGICAL_VALUE == 0) && (run_tree->type == AND))
                        {
                            if(OR_LOGICAL_VALUE != 1)
                            {
                                AND_LOGICAL_VALUE = 0;
                            }
                            OR_LOGICAL_VALUE = 0;
                        }
                        
                        if ((LOGICAL_VALUE == 1) && (run_tree->type == OR))
                        {
                            OR_LOGICAL_VALUE = 1;
                            AND_LOGICAL_VALUE = 1;
                        }
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
    //printf("Execution :3\n");
    return 0;
}
