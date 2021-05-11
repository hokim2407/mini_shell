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

#include "minishell.h"

size_t		ft_strlen(const char *str)
{
	int		i;

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

char		*ft_itoa(int num)
{
	int		divider;
	char	*result;
	int		flag;
	int		count;

	divider = 1;
	flag = (num < 0) ? -1 : 1;
	count = (num < 0) ? 2 : 1;
	while (((long)num * flag) / divider > 9)
	{
		divider *= 10;
		count++;
	}
	if (!(result = malloc(count + 1)))
		return (NULL);
	*result = '-';
	count = (num < 0) ? 1 : 0;
	while (divider > 0)
	{
		*(result + count) = '0' + (((long)num * flag) / divider) % 10;
		divider /= 10;
		count++;
	}
	*(result + count) = '\0';
	return (result);
}