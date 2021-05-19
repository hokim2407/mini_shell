/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:51:24 by hokim             #+#    #+#             */
/*   Updated: 2021/05/19 18:46:15 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_sig	g_sig;

int				sh_process(char **new_argv, t_datas *datas)
{
	int			pid;
	struct stat	buf;

	stat(new_argv[0], &buf);
	if (S_ISDIR(buf.st_mode))
		return (print_err(datas->ori_fd.write, new_argv, 2));
	if ((new_argv[0][0] != '.' && new_argv[0][0] != '/') ||
			new_argv[0][ft_strlen(new_argv[0]) - 1] == '/')
		return (print_err(datas->ori_fd.write, new_argv, 127));
	if (new_argv[0][0] != '/')
		new_argv[0] = get_abs_path(new_argv[0]);
	pid = fork();
	if (pid == 0)
	{
		sig_dfl();
		dup2(datas->fd.read, 0);
		dup2(datas->fd.write, 1);
		if (execve(new_argv[0], new_argv, datas->envv) == -1)
			exit(print_err(datas->ori_fd.write, new_argv, 127));
	}
	else
	{
		g_sig.is_cat = !ft_strcmp(new_argv[0], "cat");
		signal(SIGINT, sig_special);
		signal(SIGQUIT, sig_special);
		waitpid(pid, &datas->status, 0);
	}
	return (1);
}
