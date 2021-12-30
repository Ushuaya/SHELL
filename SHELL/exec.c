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
    if (BACK > 0)
    {
        
    
        pid_t pid;
        //int   status;
        while (((pid = waitpid(-1, NULL , WNOHANG)) != -1) && (pid != 0))
        {
            printf("[%d] stopped \n", pid);
            //printf("DUBUG SIGNAL\n");
            BACK --;
            //printf("\n__DEBUG__BACK__%d__\n", BACK);
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
    //tree tmp_tree = run_tree;
    //printf ("%s\n", *(run_tree->argv));
    
    signal(SIGCHLD, backgrnd_f);
    int LOGICAL_VALUE = 0;
    int OR_LOGICAL_VALUE = 0;
    int AND_LOGICAL_VALUE = 1;
    int LOGICAL = 0;
    //int COMMON_LOGICAL_VALUE = 1;
    int file;
    int iteration = 0;
    int Status;
    int count_OR = 0;
    int count_AND = 0;
    //int PIDS[10] = {0};
    
    
 
        
    
    int pid;
    while(run_tree)
    {
    
            if (run_tree->argv)
            {
                if (strcmp((run_tree->argv)[0], "cd\0") == 0)
                {
                    if ((run_tree->argv)[1] != NULL)
                    {
                        if(chdir ( (run_tree->argv)[1] ) != 0)
                            fprintf(stderr, "\n$$ Chdir error $$\n");
                    }
                    else
                        if(chdir (getenv("HOME")) != 0)
                            fprintf(stderr, "\n$$ Chdir error $$\n");
                    run_tree = run_tree->next;
                    continue;
                }
                else
                {
                    if (run_tree->pipe != NULL)//this is pipe!
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
                        
                        
                        if ((pid = fork())==0)
                        {
                            if (pid == -1)
                            {
                                fprintf(stderr, "\n$$ Fork error $$\n");
                                exit(1);
                            }

                            if (tmp_tree->backgrnd == 1)
                            {
                                /*
                                file = open("/dev/null", O_RDONLY);
                                dup2(file, 1);
                                dup2(file, 0);
                                close(file);
                                 */
                                signal(SIGINT, SIG_IGN);
                            }
                            close(next_in);
                            dup2(out,1);
                            close(out);
                            
                            
                            if (tmp_tree->infile)
                            {
                                file = open(tmp_tree->infile, O_RDONLY);
                                if (file == -1)
                                {
                                    fprintf(stderr, "Open file error\n");
                                    exit(1);
                                }
                                dup2(file, 0);
                                close(file);
                            }
                            
                            if (tmp_tree->outfile != NULL)
                            {
                                if (tmp_tree->append)
                                    {
                                        file = open(tmp_tree->outfile, O_WRONLY|O_APPEND, 0664);
                                        if (file == -1)
                                        {
                                            fprintf(stderr, "Open file error\n");
                                            exit(1);
                                        }
                                        dup2 (file, 1);
                                        close (file);
                                    }
                                else
                                    {
                                    file = open(tmp_tree->outfile, O_WRONLY|O_TRUNC|O_CREAT, 0664);
                                        if (file == -1)
                                        {
                                            fprintf(stderr, "Open file error\n");
                                            exit(1);
                                        }
                                    dup2 (file, 1);
                                    close (file);
                                    }
                            }
                                             
                            execvp((tmp_tree->argv)[0], tmp_tree->argv);
                            fprintf(stderr, "\n$$ Exec error $$\n");
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
                            if ((pid = fork())==0)
                            {
                                if (pid == -1)
                                {
                                    fprintf(stderr, "\n$$ Fork error $$\n");
                                    exit(1);
                                }
                                if (tmp_tree->backgrnd == 1)
                                {
                                    signal(SIGINT, SIG_IGN);
                                    /*
                                    file = open("/dev/null", O_RDONLY);
                                    dup2(file, 1);
                                    dup2(file, 0);
                                    close(file);*/
                                }
                                close(next_in);
                                dup2(in,0);
                                close(in);
                                dup2(out,1);
                                close(out);
                                //run_tree = run_tree->pipe;
                                
                                
                                
                                
                                
                                
                                if (tmp_tree->infile)
                                {
                                    file = open(tmp_tree->infile, O_RDONLY);
                                    if (file == -1)
                                    {
                                        fprintf(stderr, "Open file error\n");
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
                                                fprintf(stderr, "Open file error\n");
                                                exit(1);
                                            }
                                            dup2 (file, 1);
                                            close (file);
                                        }
                                    else
                                        {
                                        file = open(tmp_tree->outfile, O_WRONLY|O_TRUNC|O_CREAT, 0664);
                                            if (file == -1)
                                            {
                                                fprintf(stderr, "Open file error\n");
                                                exit(1);
                                            }
                                        dup2 (file, 1);
                                        close (file);
                                        }
                                }
                                
                                
                                
                                
                                
                                
                                                
                                
                                execvp((tmp_tree->argv)[0], tmp_tree->argv);
                                fprintf(stderr, "\n$$ Exec error $$\n");
                                exit(-1);
                            }
                            close(in);
                            in=next_in;
                            tmp_tree = tmp_tree->pipe;///
                        }
                        close(out);
                        if ((pid = fork())==0)
                        {
                            if (pid == -1)
                            {
                                fprintf(stderr, "\n$$ Fork error $$\n");
                                exit(1);
                            }
                            if (tmp_tree->backgrnd == 1)
                            {
                                signal(SIGINT, SIG_IGN);
                                /*
                                file = open("/dev/null", O_RDONLY);
                                dup2(file, 1);
                                dup2(file, 0);
                                close(file);*/
                            }
                            //printf("%s\n", (tmp_tree->argv)[0]);
                            dup2(in,0);
                            close(in);
                                           
                                        
                                        if (tmp_tree->infile)
                                        {
                                            file = open(tmp_tree->infile, O_RDONLY);
                                            if (file == -1)
                                            {
                                                fprintf(stderr, "Open file error\n");
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
                                                        fprintf(stderr, "Open file error\n");
                                                        exit(1);
                                                    }
                                                    dup2 (file, 1);
                                                    close (file);
                                                }
                                            else
                                                {
                                                file = open(tmp_tree->outfile, O_WRONLY|O_TRUNC|O_CREAT, 0664);
                                                    if (file == -1)
                                                    {
                                                        fprintf(stderr, "Open file error\n");
                                                        exit(1);
                                                    }
                                                dup2 (file, 1);
                                                close (file);
                                                }
                                        }
                                    

                            
                            
                            execvp((tmp_tree->argv)[0], tmp_tree->argv);
                            fprintf(stderr, "\n$$ Exec error $$\n");

                            exit(1);
                        }
                        close(in);
                        
                        if (begin_of_pipe->backgrnd == 0)
                        {
                            for( i=1; i<=stage_pipe; i++)
                            {
                                //waitpid(-1, &Status , WNOHANG);
                                wait(NULL);
                                //printf("\n%d\n", i);
                            }
                            //printf("\n__DEBUG__NOT__BACK_1_%d__\n", BACK);
                        }
                        else
                            for( i=0; i<stage_pipe; i++)
                                BACK ++;
                            //printf("\n__DEBUG__BACK_1_%d__\n", BACK);
                            
                        stage_pipe = 0;
                        iteration++;
                        
                        run_tree = run_tree->next;
                        
                        continue;
                            
                    }//END OF PIPE
                
                
                    //IF IT IS NOT A PIPE
                    if ((pid = fork())==0)
                    {
                        if (pid == -1)
                        {
                            fprintf(stderr, "\n$$ Fork error $$\n");
                            exit(1);
                        }
                        if (run_tree->backgrnd == 1)
                        {
                            signal(SIGINT, SIG_IGN);
                            //printf("\nDEBUG__BACK__NULL\n");
                            if ((file = open("/dev/null", O_RDONLY)) == -1)
                            {
                                fprintf(stderr, "\n$$ Open file errorn $$\n");
                                exit(1);
                                goto error;
                            }
                            dup2(file, 0);
                            //dup2(file, 0);
                            close(file);
                        }
                        if (run_tree->infile)
                        {
                            file = open(run_tree->infile, O_RDONLY);
                            if (file == -1)
                            {
                                fprintf(stderr, "\n$$ Open file errorn $$\n");
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
                                        fprintf(stderr, "\n$$ Open file errorn $$\n");
                                        exit(1);
                                    }
                                    dup2 (file, 1);
                                    close (file);
                                }
                            else
                                {
                                file = open(run_tree->outfile, O_WRONLY|O_TRUNC|O_CREAT, 0664);
                                    if (file == -1)
                                    {
                                        fprintf(stderr, "\n$$ Open file errorn $$\n");
                                        exit(1);
                                    }
                                dup2 (file, 1);
                                close (file);
                                }
                        }
                        
                        
                        //printf("\nDEBUG__LOG__%d__\n", LOGICAL);
                        if ((run_tree->type == OR) || (run_tree->type == AND) || LOGICAL)//CASE OF LOGICAL EXPRESSION
                        {
                            //LOGICAL = 1;
                            //printf("\nDebug_logicaL__%d__%d__%d__%d__%d__\n", OR_LOGICAL_VALUE, AND_LOGICAL_VALUE, LOGICAL_VALUE, count_OR, LOGICAL);
                            
                            if(!((OR_LOGICAL_VALUE == 1 && run_tree->type != AND && run_tree->type != NXT) || (run_tree->type == AND && AND_LOGICAL_VALUE == 0) || (OR_LOGICAL_VALUE == 0 && AND_LOGICAL_VALUE == 0) || ((count_OR>=1) && OR_LOGICAL_VALUE == 1 && (run_tree->type == AND || run_tree->type == NXT))))
                            {
                                if(execvp((run_tree->argv)[0], run_tree->argv) == -1)
                                {
                                    fprintf(stderr, "\n$$ Exec error $$\n");
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
                            //printf("\nDEBUG___ %s ___\n", (run_tree->argv)[0]);
                            if(execvp((run_tree->argv)[0], run_tree->argv) == -1)
                            {
                                fprintf(stderr, "\n$$ Exec error $$\n");
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
                    if (run_tree->backgrnd == 0)
                    {
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
                            //AND_LOGICAL_VALUE = 0;
                        }
                        //printf("Debug_logicaL__%d__\n", LOGICAL_VALUE);


                        if((run_tree->type == OR) || (run_tree->type == AND) || LOGICAL)
                        {
                            LOGICAL = 1;
                            if (run_tree->type == AND)
                            {
                                count_OR = 0;
                                count_AND++;
                            }
                            if (run_tree->type == OR)
                            {
                                count_AND = 0;
                            }
                            if (count_AND >= 2)
                            {
                                OR_LOGICAL_VALUE = 0;
                            }
 
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
                                count_OR++;
                            }
                            
                        }
                    }
                    else
                    {
                        BACK ++;
                        //printf("\n__DEBUG__BACK_2_%d__\n", BACK);

                    }
                        

                
                
                
                
                
          
                }
        
            }
            else
            {
                fprintf(stderr, "\n$$ Exec error $$\n");
                //error
            }
            
            iteration++;
            run_tree = run_tree->next;
        
        
    }
        
    

error:
//end:
    //printf("Execution :3\n");
    return 0;
}
