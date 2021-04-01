#include "minishell.h"



int sh_process(char **new_argv, t_datas datas)
{
    int pid;
    char *temp;
    if(new_argv[0][ft_strlen(new_argv[0])-1]=='/')
    return 1;

    if(new_argv[0][0] != '/')
        new_argv[0] = get_abs_path(new_argv[0]);
    pid = fork();
    if (pid == 0)
    {
        if (execve(new_argv[0], new_argv, datas.envv) == -1)
            return ft_write("execve error\n");
        free(temp);
    }
    else
     {
        wait(NULL);
        exit(0);
       }

    return 1;
}