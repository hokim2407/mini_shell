
#include "minishell.h"

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

int mini_process(char *buf, char **envv, t_deck *env_lst)
{
	char **new_argv;
	int i;

    i=-1;
	new_argv = ft_split(buf, ' ');
    
    while (new_argv[++i])
        check_env_in_cmd(new_argv + i, env_lst);
	if (new_argv[0] == NULL)
		return 1;
	if (!ft_strcmp(new_argv[0], "ls") || !ft_strcmp(new_argv[0], "pwd") || !ft_strcmp(new_argv[0], "echo"))
		exe_process(new_argv, envv, env_lst);
	else if (!ft_strcmp(new_argv[0], "cd") && new_argv[1] != NULL)
		chdir(new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "env"))
		ft_print_all_deck(*env_lst);
	else if (!ft_strcmp(new_argv[0], "export"))
		ft_add_env(env_lst, new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "unset"))
		ft_rm_env(env_lst, new_argv[1]);
	else if (new_argv[0][0]== '/' || !ft_strlcmp(new_argv[0], "./", 2)|| !ft_strlcmp(new_argv[0], "../", 3))
            sh_process(new_argv, envv, env_lst);
	else if (!ft_strcmp(new_argv[0], "exit"))
		exit(0);
	return 1;
}

int main(int argc, char **argv, char **envv)
{
	char buf[4096];
	char **new_argv;
	t_deck *env_lst = array_to_list(envv);
	head = "mini_shell> ";
	char ** splited;
	//getcwd(path, 256);
	//signal(SIGINT, sig_ft);

	while (1)
	{
		read_fd = 0;
		write_fd = 1;
		write(1, head, ft_strlen(head));
		int i = 0;
		while (read(0, buf + i, 1) > 0 && buf[i] != '\n')
			i++;
		if (buf[i] != '\n')
			write(1, "\n", 1);
		buf[i] = '\0';
		if (buf[0] == '\0' || buf[0] == '\n')
			continue;
	
		mini_process(splited[1],envv, env_lst);
	}
}
