/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils_make.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:51:07 by hokim             #+#    #+#             */
/*   Updated: 2021/05/21 22:03:34 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	int				i;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	if (!(result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (*s1 != '\0')
	{
		*(result + i) = *(s1++);
		i++;
	}
	while (*s2 != '\0')
	{
		*(result + i) = *(s2++);
		i++;
	}
	*(result + i) = '\0';
	return (result);
}

size_t				ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (!src)
		return (0);
	if (!dest || size == 0)
		return (ft_strlen(src));
	while (*(src + i) != '\0' && i + 1 < size)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (ft_strlen(src));
}

char				*ft_strdup(const char *str)
{
	char			*result;

	if (!(result = malloc(ft_strlen(str) + 1)))
		return (NULL);
	ft_strlcpy(result, str, ft_strlen(str) + 1);
	return (result);
}

int				ft_atoi(const char *str, char **new_argv)
{
	long long		value;
	int				flag;
	int				i;

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
		if (value == 922337203685477580 && *(str + i) != '\0' && *(str + i) >= '8')
			exit(print_err(2, new_argv, 255));
	}
	return (int)value * flag;
}

char				*ft_itoa(int num)
{
	int				divider;
	char			*result;
	int				flag;
	int				count;

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
