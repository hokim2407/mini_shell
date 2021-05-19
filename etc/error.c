/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:30:35 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/19 18:46:29 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			print_err(int fd, char **argv, int status)
{
	int		len;

	len = -1;
	fd = 2;
	while (argv[++len])
		;
	ft_write(1, "minishell: ");
	ft_write(fd, argv[0]);
	ft_write(fd, ": ");
	if (status == 127)
		ft_write(fd, "command not found\n");
	else if (status == 1)
		ft_write(fd, "too many arguments\n");
	else if (status == 2)
		ft_write(fd, "is a directory\n");
	else if (status == 255)
	{
		ft_write(fd, argv[1]);
		ft_write(fd, ": numeric argument required\n");
	}
	else
	{
		ft_write(fd, argv[len - 1]);
		ft_write(fd, ": ");
		ft_write(fd, strerror(errno));
		ft_write(fd, "\n");
	}
	return (status);
}

int			print_env_err(int fd, char **argv)
{
	int		len;

	len = -1;
	fd = 2;
	while (argv[++len])
		;
	ft_write(fd, argv[0]);
	ft_write(fd, ": ");
	ft_write(fd, argv[len - 1]);
	ft_write(fd, ": ");
	ft_write(fd, "No such file or directory");
	ft_write(fd, "\n");
	return (1);
}

int			print_export_err(int fd, char *cmd, char *err_cmd)
{
	int		len;

	len = -1;
	fd = 2;
	ft_write(fd, "minishell: ");
	ft_write(fd, cmd);
	ft_write(fd, ": `");
	ft_write(fd, err_cmd);
	ft_write(fd, "\': ");
	ft_write(fd, "not a valid identifier");
	ft_write(fd, "\n");
	return (1);
}

int			print_syntax_error(int fd, char *token, int token_num)
{
	fd = 2;
	ft_write(fd, "minishell: syntax error near unexpected token `");
	if(token_num %10 > 2 && token_num/ 10 < 2)
		ft_write(fd,"newline");
	else if((token_num %10 > 1 && (token_num/10) > 2)|| (token_num %10 < 3 &&  token_num > 10))
		write(fd,token,2);
	else
		write(fd,token,1);
	ft_write(fd, "\'\n");
	return (258);
}


int			is_err_token(char *str)
{
	int i;
	int value = 0;;
	i = 0;

	if (*str == ';')
		value = 1;
	if (*str == '|')
		value = 2;
	if (*str == '<')
		value = 3 ;
	if (*str == '>')
		value = 4;
	if(value == 0)
		return value;
	while (str[i] == *str)
			i++;
	value += 10 * (i - 1);
	return value;
}
int			syntax_error_check(int fd, char *buf)
{
	char	**strs;
	int i;
	int j;
	int err_token;

	i = -1;
	strs = ft_split(buf,' ');
	while (strs[++i])
	{
		j = -1;
		while (strs[i][++j])
		{
			err_token = is_err_token(strs[i]+j);
			if (err_token && (
				(i == 0 && j == 0) || err_token > 20 || (err_token == 11) 
				|| (err_token % 10 > 1&& strs[i][j + err_token / 10 + 1] == '\0' && strs[i + 1] == NULL)
				))
			{
				print_syntax_error(fd, strs[i] + j, err_token);
				return 0;
			}
		}
	}
	return (1);
}