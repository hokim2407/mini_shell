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

int		write_redirect(char *pipe, t_fd ori_fd, t_fd *fd, int i)
{

	int create;
	char * filename;

	pipe[i] = ' ';
	create = 0;
	if (pipe[i + 1] && pipe[i + 1] == '>')
	{
		i++;
		pipe[i] = ' ';
		create = O_WRONLY | O_APPEND | O_CREAT;
	}
	else
		create = O_WRONLY | O_TRUNC | O_CREAT;
	filename = get_filename_from(pipe + i + 1);
	fd->write = open(filename, create, S_IRWXU | S_IRWXG | S_IRWXO);
	free(filename);
	if (fd->write == -1)
	{
		print_err(ori_fd.write);
		return 0;
	}

	return 1;
}

int		check_redirect(char *pipe, t_fd ori_fd, t_fd *fd)
{
	int		i;
	char	*filename;

	i = -1;
	while (pipe[++i])
	{
		if (pipe[i] == '>')
			return write_redirect(pipe, ori_fd, fd, i);
		else if (pipe[i] == '<')
		{
			pipe[i] = ' ';
			filename = get_filename_from(pipe + i + 1);
			fd->read = open(filename, O_RDONLY);
			free(filename);
			 if (fd->read == -1)
			 {
				print_err(ori_fd.write);
			 	return 0;
			 }
		}
	}
	return 1;
}

