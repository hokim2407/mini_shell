/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:39:10 by hokim             #+#    #+#             */
/*   Updated: 2021/05/23 20:17:33 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			print_syntax_error(int fd, char *token, int token_num)
{
	ft_write(fd, ERR_HEADER);
	ft_write(fd, "syntax error near unexpected token `");
	if (token_num % 10 > 2 && token_num / 10 < 2)
		ft_write(fd, "newline");
	else if ((token_num % 10 > 1 && (token_num / 10) > 2) ||
			(token_num % 10 < 3 && token_num > 10))
		write(fd, token, 2);
	else
		write(fd, token, 1);
	ft_write(fd, "\'\n");
	return (258);
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

int			is_syntax_err(char **strs, int *err_token, int i, int j)
{
	if (*err_token && ((*err_token % 10 < 3 && i == 0 && j == 0) ||
		*err_token > 20 || (*err_token == 11) || (*err_token % 10 > 1
		&& strs[i][j + *err_token / 10 + 1] == '\0' && strs[i + 1] == NULL)))
		return (1);
	return (0);
}

int			check_continuous_syntex_err(int fd, char *buf, int *status)
{
	int		i;
	int		err_token;
	int		pre_token;

	i = -1;
	pre_token = 0;
	while (buf[++i])
	{
		if (buf[i] == ' ')
			continue;
		err_token = is_err_token(buf + i);
		if (err_token > 0 && pre_token > 0)
		{
			if (err_token % 10 > 2)
				err_token += 20;
			print_syntax_error(fd, buf + i, err_token);
			*status = 258;
			return (1);
		}
		pre_token = err_token;
		i += err_token / 10;
	}
	return (0);
}

int			syntax_error_check(int fd, char *buf, int *status)
{
	char	**strs;
	int		j;
	int		err_token;
	int		i;

	i = -1;
	if (check_continuous_syntex_err(fd, buf, status))
		return (0);
	strs = ft_split(buf, ' ');
	while (strs[++i])
	{
		j = -1;
		while (strs[i][++j])
		{
			err_token = is_err_token(strs[i] + j);
			if (is_syntax_err(strs, &err_token, i, j) && !get_quato(strs[i], j))
			{
				*status = print_syntax_error(fd, strs[i] + j, err_token);
				free_str_array(strs);
				return (0);
			}
		}
	}
	free_str_array(strs);
	return (1);
}
