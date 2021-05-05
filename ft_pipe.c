
#include "minishell.h"

#define READ 0
#define WRITE 1

void recur_pipe(char **argv, t_datas *datas, int count, int read_fd)
{

	int fd_pread[2];
	int fd_cread[2];
	char c;
	pid_t pid;

	pipe(fd_pread);
	pipe(fd_cread);

	pid = fork();

	if (pid == 0)
	{
		datas->ori_fd.write = dup(1);
		 datas->ori_fd.read = dup(0);
		close(fd_cread[1]);
		check_redirect(argv[count], &datas->fd);


		if (datas->fd.read == 0)
			dup2(fd_cread[0], 0);
		else
			dup2(datas->fd.read, 0);

		if (datas->fd.write != 1)
			dup2(datas->fd.write, 1);
		else if (argv[count + 1] == NULL)
			dup2(datas->ori_fd.write, 1);
		else
			dup2(fd_pread[1], 1);
		

		mini_pipe_process(argv[count], datas);
		/*	while (read(fd_cread[0], &c,1) > 0)
		{
			c += 1;
			write(1, &c,1);
		}
*/
		close(fd_cread[0]);
		close(fd_pread[1]);

		dup2(datas->ori_fd.read, 0);
		dup2(datas->ori_fd.write, 1);
		if (argv[count + 1] != NULL && datas->status == 0)
		{
				recur_pipe(argv, datas, count + 1, fd_pread[0]);

		}
	}
	else
	{
		close(fd_cread[0]);
		//printf("\n*recieve fd = %d*\n", read_fd);
		if (read_fd != 0)
			while (read(read_fd, &c, 1) > 0)
			{
				write(fd_cread[1], &c, 1);

			}

		close(fd_cread[1]);
		close(read_fd);
		close(fd_pread[1]);
		close(fd_pread[0]);
		waitpid(pid, &datas->status, 0);
	}
}

int pipe_process(char *block, t_datas *datas)
{

	pid_t pid;

	char **pipes;
	int i = -1;
	pipes = ft_split(block, '|');

	if (pipes[1] == NULL)
	{
		mini_single_process(pipes[0], datas);
		if(datas->status > 0)
           write(1,"execve error\n",13);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			recur_pipe(pipes, datas, 0, 0);
			exit(datas->status/256);
		}
		else
		{
				waitpid(pid, &datas->status, 0);
				if(datas->status > 0)
                write(1,"execve error\n",13);

		}
	}
	return 1;
}
