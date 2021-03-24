/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 20:19:51 by hokim             #+#    #+#             */
/*   Updated: 2021/03/10 17:20:16 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			free_array(char **result, int index)
{
	int		i;

	i = 0;
	while (i < index)
		free(result[index]);
	free(result);
	return (0);
}

int			count_str(char *str, char c)
{
	int		count;

	count = 0;
	while (*str == c && *str)
		str++;
	if (*str != c && *str)
	{
		while (*str != c && *str)
		{
			count++;
			str++;
		}
	}
	return (count);
}

int			fill_data(char *str, char c, char **result, int count)
{
	int		index;

	index = 0;
	while (*str && index < count)
	{
		while (*str == c && *str)
			str++;
		if (!*str)
		{
			result[index] = NULL;
			return (1);
		}
		if (!(result[index] = malloc(count_str(str, c) + 1)))
			return (free_array(result, index));
		ft_strlcpy(result[index], str, count_str(str, c) + 1);
		str += count_str(str, c);
		index++;
	}
	result[index] = NULL;
	return (1);
}

int			count_split(char *str, char c)
{
	int		count;

	count = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str != c && *str)
		{
			while (*str != c && *str)
				str++;
			count++;
		}
	}
	return (count);
}

char		**ft_split(char const *str, char c)
{
	int		count;
	char	**result;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	count = count_split((char*)str, c);
	if (!(result = malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	if (count == 0)
	{
		*result = NULL;
		return (result);
	}
	if (!fill_data((char*)str, c, result, count))
		return (NULL);
	return (result);
}
