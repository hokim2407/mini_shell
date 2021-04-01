
#include "minishell.h"
#include <string.h>
#include <errno.h>
pid_t pid;
char *head;
	int read_fd;
	int write_fd;
void sig_ft()
{
	if (SIGINT != 2)
		signal(SIGINT, SIG_DFL);
	else
	{
		write(1, "\n", 1);
		write(1, head, ft_strlen(head));
	}
}

int mini_pipe_process(char *buf, t_datas datas)
{
	char **new_argv;
	int i;

    i=-1;
	new_argv = ft_split(buf, ' ');
 	
    while (new_argv[++i])
        check_env_in_cmd(new_argv + i, datas.env_list);
	if (new_argv[0] == NULL)
		return 1;
	if (!ft_strcmp(new_argv[0], "cd") && new_argv[1] != NULL)
		;
	else if (!ft_strcmp(new_argv[0], "env"))
		;
	else if (!ft_strcmp(new_argv[0], "export"))
		;
	else if (!ft_strcmp(new_argv[0], "unset"))
		;
	else if (!ft_strcmp(new_argv[0], "exit"))
		exit(0);
	else if (new_argv[0][0]== '/' || !ft_strlcmp(new_argv[0], "./", 2)|| !ft_strlcmp(new_argv[0], "../", 3))
            sh_process(new_argv, datas);
	else
		exe_process(new_argv, datas);
    return 1;
    
}

int mini_single_process(char *buf, t_datas datas)
{
	char **new_argv;
	int i;

    i=-1;
	new_argv = ft_split(buf, ' ');
 	
    while (new_argv[++i])
        check_env_in_cmd(new_argv + i, datas.env_list);
	if (new_argv[0] == NULL)
		return 1;
	if (!ft_strcmp(new_argv[0], "cd") && new_argv[1] != NULL)
		chdir(new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "env"))
		ft_print_all_deck(*datas.env_list);
	else if (!ft_strcmp(new_argv[0], "export"))
		ft_add_env(datas.env_list, new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "unset"))
		ft_rm_env(datas.env_list, new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "exit"))
		exit(0);
	else if (new_argv[0][0]== '/' || !ft_strlcmp(new_argv[0], "./", 2)|| !ft_strlcmp(new_argv[0], "../", 3))
            sh_process(new_argv, datas);
	else
		exe_process(new_argv, datas);
    return 1;
    
}

int main(int argc, char **argv, char **envv)
{
	char buf[4096];
	t_datas datas;
	char **new_argv;
	head = "mini_shell> ";
	char ** blocks;
	int i ;
	datas.env_list = array_to_list(envv);
	datas.envv = envv;
	while (1)
	{
		
		datas.fd.read = 0;
		datas.fd.write = 1;
		write(1, head, ft_strlen(head));
		int i = 0;
		while (read(0, buf + i, 1) > 0 && buf[i] != '\n')
			i++;
		if (buf[i] != '\n')
			write(1, "\n", 1);
		buf[i] = '\0';
		if (buf[0] == '\0' || buf[0] == '\n')
			continue;
		blocks = ft_split(buf, ';');
		i = -1;
		
		while(blocks[++i])
		{
			pipe_process (blocks[i], datas);
		}
	}
}
