
#include "minishell.h"

#define READ 0
#define WRITE 1

int refeat_pipe(char *argv, t_datas *datas, pid_t * pid, int fd_read, int is_final)
{
	int fd_pipe[2];
	char c;

	pipe(fd_pipe);
	*pid = fork();

	if (*pid == 0)
	{
		close(fd_pipe[0]);
		check_redirect(argv, &datas->fd);
		dup2(fd_read, 0);
		if (is_final)
			dup2(datas->ori_fd.write, 1);
		else
			dup2(fd_pipe[1] ,1);
		mini_single_process(argv, datas);

		close(fd_pipe[1]);
		close(fd_read);
		exit(datas->status/256);
	}
	close(fd_pipe[1]);
	close(fd_read);
	return fd_pipe[0];
}



void start_pipe(char **pipes, t_datas *datas)
{
	pid_t pid;
	pid_t *child_pid;
	int count;
	int i;

	count = -1;

	while(pipes[++count])
	;
	child_pid = malloc(sizeof(pid_t)* count);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		i = -1;
		datas->fd.read = 0;
		while(pipes[++i])
		{
			datas->fd.read = refeat_pipe(pipes[i], datas, child_pid + i, 	datas->fd.read , pipes[i + 1] == NULL);
			
			
		}
		i = -1;
		while(pipes[++i])
		{
			waitpid(child_pid[i], &datas->status, 0);

		}
		exit(WEXITSTATUS(datas->status));
	}
	else
	{
		waitpid(pid, &datas->status, 0);
	}
	free(child_pid);
}

int pipe_process(char *block, t_datas *datas)
{
	char **pipes;
	int i = -1;
	
	pipes = ft_split(block, '|');
	datas->ori_fd.write = dup(1);
	datas->ori_fd.read = dup(0);
	if (pipes[1] == NULL)
	{
		datas->fd.read = 0;
		datas->fd.write = 1;
		check_redirect(pipes[0], &datas->fd);
		mini_single_process(pipes[0], datas);
	}
	else
	{
		start_pipe(pipes, datas);
	}
	free_str_array(pipes);
	return 1;
}
