/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:51:24 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:51:27 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			sh_process(char **new_argv, t_datas *datas)
{
	int		pid;
	char	*temp;

	if (new_argv[0][ft_strlen(new_argv[0]) - 1] == '/')
		return (1);
	if (new_argv[0][0] != '/')
		new_argv[0] = get_abs_path(new_argv[0]);
	pid = fork();
	if (pid == 0)
	{
		if (execve(new_argv[0], new_argv, datas->envv) == -1)
			exit(1);
		free(temp);
	}
	else
	{
		wait(&datas->status);
		exit(datas->status);
	}
	return (1);
}
