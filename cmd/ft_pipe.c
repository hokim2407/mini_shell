/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:12:25 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/11 19:45:48 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			refeat_pipe(char *argv, t_datas *datas, pid_t *pid,
		int is_final)
{
	int		fd_pipe[2];

	pipe(fd_pipe);
	*pid = fork();
	if (*pid == 0)
	{
		close(fd_pipe[0]);
		if (!check_redirect(argv, datas))
			exit(1);
		dup2(datas->fd.read, 0);
		if (is_final)
			dup2(datas->ori_fd.write, 1);
		else
			dup2(fd_pipe[1], 1);
		mini_single_process(argv, datas);
		close(1);
		close(datas->fd.read);
		exit(datas->status / 256);
	}
	close(fd_pipe[1]);
	close(datas->fd.read);
	return (fd_pipe[0]);
}

int			count_arr(char **arr)
{
	int count;

	count = -1;
	while (arr[++count])
		;
	return (count);
}

void		start_pipe(char **pipes, t_datas *datas)
{
	pid_t	pid;
	pid_t	*child_pid;
	int		count;
	int		i;

	count = count_arr(pipes);
	child_pid = malloc(sizeof(pid_t) * count);
	pid = fork();
	if (pid == 0)
	{
		i = -1;
		datas->fd.read = dup(0);
		while (pipes[++i])
			datas->fd.read = refeat_pipe(pipes[i], datas, child_pid + i,
					pipes[i + 1] == NULL);
		i = -1;
		while (pipes[++i])
			waitpid(child_pid[i], &datas->status, 0);
		exit(WEXITSTATUS(datas->status));
	}
	else
		waitpid(pid, &datas->status, 0);
	free(child_pid);
}

int			pipe_process(char *block, t_datas *datas)
{
	char	**pipes;
	int		i;

	i = -1;
	pipes = ft_split(block, '|');
	datas->ori_fd.write = dup(1);
	datas->ori_fd.read = dup(0);
	if (pipes[1] == NULL)
	{
		datas->fd.write = 1;
		datas->fd.read = 0;
		if (!check_redirect(pipes[0], datas))
		{
			free_str_array(pipes);
			return (1);
		}
		mini_single_process(pipes[0], datas);
	}
	else
		start_pipe(pipes, datas);
	free_str_array(pipes);
	datas->status/=256;
	return (1);
}
