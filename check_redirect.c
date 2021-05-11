/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:56:56 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/11 14:53:58 by hyerkim          ###   ########.fr       */
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

int		write_redirect(char *pipe, t_datas *datas, t_fd *fd, int i)
{
	char	**str;

	str = NULL;
	if (pipe[i] == '>' && pipe[i + 1] && pipe[i + 1] == '>')
	{
		pipe[i] = ' ';
		i++;
		pipe[i] = ' ';
		/*
		*/
		str = ft_split(pipe, ' ');
		fd->write = open(get_filename_from(pipe + i + 1),
					O_WRONLY | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	}
	else if (pipe[i] == '>')
	{
		pipe[i] = ' ';
		/*
		*/
		str = ft_split(pipe, ' ');
		fd->write = open(get_filename_from(pipe + i + 1),
					O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	}
	if (fd->write == -1)
	{
		datas->status = print_err(datas->ori_fd.write, str, 22);
		if(str != NULL)
			free_str_array(str);
		return 0;
	}
	if(str != NULL)
		free_str_array(str);
	return 1;
}

int		check_redirect(char *pipe, t_datas *datas, t_fd *fd)
{
	int		i;
	char	**str;

	str = NULL;
	i = -1;
	while (pipe[++i])
	{
		if (pipe[i] == '>')
			return write_redirect(pipe, datas, fd, i);
		else if (pipe[i] == '<')
		{
			pipe[i] = ' ';
			 str = ft_split(pipe, ' ');
			fd->read = open(get_filename_from(pipe + i + 1), O_RDONLY);
			if (fd->read == -1)
			{
				
				 datas->status = print_err(datas->ori_fd.write, str, 22);
				 free_str_array(str);
				return 0;
			}
			if(str != NULL)
				free_str_array(str);
		}
	}
	return 1;
}

