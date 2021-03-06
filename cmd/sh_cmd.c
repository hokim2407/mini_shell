/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:51:24 by hokim             #+#    #+#             */
/*   Updated: 2021/05/21 20:51:17 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_sig	g_sig;

int				sh_err_check(char **new_argv, t_datas *datas)
{
	struct stat	buf;
	int			result;

	result = stat(new_argv[0], &buf);
	if ((result == -1 && new_argv[0][0] == '/'))
	{
		errno = 2;
		redirect_err(datas->ori_fd.err, new_argv[0], 1);
		datas->status = 127 * 256;
	}
	else if (S_ISDIR(buf.st_mode))
		datas->status = print_err(datas->ori_fd.err, new_argv, 126) * 256;
	else if ((new_argv[0][0] != '.' && new_argv[0][0] != '/') ||
			new_argv[0][ft_strlen(new_argv[0]) - 1] == '/')
		print_err(datas->ori_fd.err, new_argv, 127);
	else
		return (1);
	return (0);
}

int				sh_process(char **new_argv, t_datas *datas)
{
	int			pid;

	if (!sh_err_check(new_argv, datas))
		return (0);
	if (new_argv[0][0] != '/')
		new_argv[0] = get_abs_path(new_argv[0]);
	pid = fork();
	if (pid == 0)
	{
		sig_dfl();
		dup2(datas->fd.read, 0);
		dup2(datas->fd.write, 1);
		if (execve(new_argv[0], new_argv, datas->envv) == -1)
			exit(print_err(datas->ori_fd.err, new_argv, 127));
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
