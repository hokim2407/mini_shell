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

int exe_process(char **new_argv, t_datas datas)
{
    int pid;
    char *temp;

    pid = fork();
    if (pid == 0)
    {   
        temp = get_executable(find_value_in_list(datas.env_list,"PATH") ,new_argv[0]);
        dup2(datas.fd.read,0);
        dup2(datas.fd.write,1);
     
        if (execve(temp, new_argv, datas.envv) == -1)
            return write(1,"execve error\n",13);
        if(datas.fd.read != 0)
            close(datas.fd.read);
        if(datas.fd.write != 1)
            close(datas.fd.write);
        free(temp);
    }
    else
        wait(NULL);

    return 1;
}