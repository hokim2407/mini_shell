/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:39:10 by hokim             #+#    #+#             */
/*   Updated: 2021/05/19 21:45:04 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			print_syntax_error(int fd, char *token, int token_num)
{
	fd = 2;
	ft_write(fd, "minishell: syntax error near unexpected token `");
	if (token_num % 10 > 2 && token_num / 10 < 2)
		ft_write(fd, "newline");
	else if ((token_num % 10 > 1 && (token_num / 10) > 2) ||
			(token_num % 10 < 3 && token_num > 10))
		write(fd, token, 2);
	else
		write(fd, token, 1);
	ft_write(fd, "\'\n");
	return (1);
}

int			is_err_token(char *str)
{
	int		i;
	int		value;

	i = 0;
	value = 0;
	if (*str == ';')
		value = 1;
	if (*str == '|')
		value = 2;
	if (*str == '<')
		value = 3;
	if (*str == '>')
		value = 4;
	if (value == 0)
		return (value);
	while (str[i] == *str)
		i++;
	value += 10 * (i - 1);
	return (value);
}

int			syntax_error_check(int fd, char *buf, int *status)
{
	char	**strs;
	int		i;
	int		j;
	int		err_token;

	i = -1;
	strs = ft_split(buf, ' ');
	while (strs[++i])
	{
		j = -1;
		while (strs[i][++j])
		{
			err_token = is_err_token(strs[i] + j);
			if (get_quato(strs[i], j) != 0)
				continue;
			if (err_token && ((i == 0 && j == 0) || err_token > 20 ||
			(err_token == 11) || (err_token % 10 > 1 &&
			strs[i][j + err_token / 10 + 1] == '\0' && strs[i + 1] == NULL)))
			{
				*status = print_syntax_error(fd, strs[i] + j, err_token);
				return (0);
			}
		}
	}
	return (1);
}
