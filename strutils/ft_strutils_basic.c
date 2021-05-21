/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils_basic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:50:53 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:50:56 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

int			ft_write(int fd, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		;
	write(fd, str, i);
	return (1);
}

int			ft_write_ch(int c)
{
	write(1, &c, 1);
	return (1);
}

int			ft_strchr(const char *str, int value)
{
	int		i;

	i = 0;
	if (*str == '\0' && value == 0)
		return (-1);
	while (*(str + i) != '\0')
	{
		if (*(str + i) == value)
			return (i);
		i++;
	}
	if (*(str + i) == value)
		return (i);
	return (-1);
}

int			is_n_option(char *argv)
{
	int		i;

	i = 0;
	if (argv[i] == '-')
	{
		while (argv[++i] == 'n')
			;
		if (i > 1 && argv[i] == '\0')
		{
			argv[2] = '\0';
			return (1);
		}
	}
	return (0);
}
