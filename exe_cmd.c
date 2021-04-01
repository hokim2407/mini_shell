#include "minishell.h"
extern	int read_fd;
extern	int write_fd;

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

int exe_process(char **new_argv, char **envv, t_deck *env_list)
{
    int pid;
    char *temp;

    pid = fork();
    if (pid == 0)
    { 
        temp = get_executable(find_value_in_list(env_list,"PATH") ,new_argv[0]);
     //   dup2(read_fd,0);
    //    dup2(write_fd,1);
        if (execve(temp, new_argv, envv) == -1)
            return write(1,"execve error\n",13);
        if(read_fd != 0)
            close(read_fd);
        if(write_fd != 0)
            close(write_fd);
        free(temp);
    }
    else
        wait(NULL);

    return 1;
}