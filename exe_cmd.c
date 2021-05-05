#include "minishell.h"

int in_dir(char * path, char * cmd)
{
    DIR     *dir_ptr = NULL;
    struct dirent *file = NULL;
   
    if((dir_ptr = opendir(path)) == NULL) 
        return 0;

    while((file = readdir(dir_ptr)))
    {
        if(!ft_strcmp(file->d_name, cmd))
            return 1;
    }
    closedir(dir_ptr);
    return 0;

}

char * get_executable(char * path, char *cmd)
{
    char **paths = ft_split(path, ':');

    int i = -1;
    char * temp = NULL;
    while(paths[++i])
    {
        if(in_dir(paths[i],cmd))
        break;
    }
    if(paths[i])
    {
        temp = paths[i];
        paths[i] = ft_strjoin(paths[i], "/");
        free(temp);
        temp = ft_strjoin(paths[i], cmd);
    }
    free_str_array(paths);
    return temp;
}

int exe_process(char **new_argv, t_datas *datas)
{
    int pid;
    char *temp;
    int status;
    int limit= 20000000;
  
    pid = fork();

    if (pid == 0)
    {
        temp = get_executable(find_value_by_key(datas->env_list,"PATH") ,new_argv[0]);
        dup2(datas->fd.read,0);
        dup2(datas->fd.write,1);

        if (execve(temp, new_argv, datas->envv) == -1)
            {
                if (!ft_strcmp(new_argv[0], "cd") || !ft_strcmp(new_argv[0], "env") || !ft_strcmp(new_argv[0], "export") || !ft_strcmp(new_argv[0], "unset")|| !ft_strcmp(new_argv[0], "exit"))
	                exit(0);
                exit(1);
            }

    }
    else
        {
            waitpid(pid,&datas->status,0);
        }
    return 1;
}