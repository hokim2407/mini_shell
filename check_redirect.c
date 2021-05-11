/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:56:56 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/11 17:56:22 by hyerkim          ###   ########.fr       */
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
	int create;
	char * filename;


	str = NULL;
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
    str = ft_split(pipe, ' ');
	filename = get_filename_from(pipe + i + 1);

	fd->write = open(filename, create, S_IRWXU | S_IRWXG | S_IRWXO);


	free(filename);
	if (datas->fd.write == -1)
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
	char	*filename;

	str = NULL;
	i = -1;
	while (pipe[++i])
	{
		if (pipe[i] == '>')
			return write_redirect(pipe, datas, &datas->fd, i);
		else if (pipe[i] == '<')
		{
			pipe[i] = ' ';
			str = ft_split(pipe, ' ');
			filename = get_filename_from(pipe + i + 1);
			fd->read = open(filename, O_RDONLY);
			free(filename);
			if (datas->fd.read == -1)
			{

				datas->status = print_err(datas->ori_fd.write, str, 22);
				free_str_array(str);
				return 0;
			}
			if (str != NULL)
				free_str_array(str);
		}
	}
	return 1;
}

