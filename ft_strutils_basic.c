/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:48:17 by hokim             #+#    #+#             */
/*   Updated: 2021/04/01 17:18:16 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

int			ft_write(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		;
	write(1, str, i);
	return 1;
}

int			ft_write_ch(int c)
{
	write(1, &c, 1);
	return 1;
}

int		ft_strchr(const char *str, int value)
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

int			ft_atoi(const char *str)
{
	int		value;
	int		flag;
	int		i;

	i = 0;
	value = 0;
	flag = 1;
	while ((*(str + i) > 8 && *(str + i) < 14) || *(str + i) == 32)
		i++;
	if (*(str + i) == '+')
		i++;
	else if (*(str + i) == '-')
	{
		i++;
		flag *= (-1);
	}
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		value = value * 10 + *(str + i) - '0';
		i++;
	}
	return (int)value * flag;
}
