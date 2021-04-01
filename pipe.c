#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include  <signal.h>


#define READ 0
#define WRITE 1

int ori_write_fd;

void recur_pipe(char **argv, int count, int read_fd)
{

	int fd_pread[2];
	int fd_cread[2];
	char c;

	pid_t pid;

	pipe(fd_pread);
	pipe(fd_cread);
	pid = fork();

	if(pid == 0)
	{
		close(fd_cread[1]);
		dup2(fd_cread[0],0);
		dup2(fd_pread[1],1);
		if(argv[count + 1] == NULL)
			dup2(ori_write_fd,1);
		while (read(0, &c,1) > 0)
		{
			c += 1;
			write(1, &c,1);
		}

		close(fd_cread[0]);
		close(fd_pread[1]);

		//printf("\n*send = %d*\n", fd_pread[0]);

		if(argv[count + 1] != NULL)
			recur_pipe(argv,count+1 ,fd_pread[0]);

		exit(0);
	}
	else
	{ 
		close(fd_cread[0]);
		dup2(read_fd,0);
		dup2(fd_cread[1],1);
		//printf("\n*recieve fd = %d*\n", read_fd);
		while (read(0, &c,1) > 0  )
		{
			write(1, &c, 1);
		}
		close(0);
		close(1);
		close(fd_cread[1]);
		close(read_fd);
		close(fd_pread[1]);
		close(fd_pread[0]);
		waitpid(pid, NULL,0);
	}

}

int pipe_process (int argc, char **argv)
{

	pid_t pid = fork();
	ori_write_fd = dup(1);
	if(pid == 0)
		recur_pipe(argv,0,0);
	else
		waitpid(pid, NULL,0);
return 1;
}
