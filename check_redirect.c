/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:56:56 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/09 16:56:58 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_filename_from(char *str)
{
	char	*result;
	int		chr;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	i = -1;
	j = -1;
	while (str[++i] == ' ')
		;
	while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
	{
		result[++j] = str[i++];
		str[i - 1] = ' ';
	}
	result[++j] = '\0';
	return (result);
}

void		write_redirect(char *pipe, t_fd *fd, int i)
{
	if (pipe[i] == '>' && pipe[i + 1] && pipe[i + 1] == '>')
	{
		pipe[i] = ' ';
		i++;
		pipe[i] = ' ';
		fd->write = open(get_filename_from(pipe + i + 1),
					O_WRONLY | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
		if (fd->write == -1)
			fd->write = 1;
	}
	else if (pipe[i] == '>')
	{
		pipe[i] = ' ';
		fd->write = open(get_filename_from(pipe + i + 1),
					O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
		if (fd->write == -1)
			fd->write = 1;
	}
}

void		check_redirect(char *pipe, t_fd *fd)
{
	int		i;

	i = -1;
	while (pipe[++i])
	{
		if (pipe[i] == '>')
			write_redirect(pipe, fd, i);
		else if (pipe[i] == '<')
		{
			pipe[i] = ' ';
			fd->read = open(get_filename_from(pipe + i + 1), O_RDONLY);
			if (fd->read == -1)
				fd->read = 0;
		}
	}
}
