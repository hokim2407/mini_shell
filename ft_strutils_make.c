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

void free_str_array(char **str)
{
	int i;

	if (str == NULL)
		return;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	char *result;
	int i;

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

char		*ft_strdup(const char *str)
{
	char	*result;

	if (!(result = malloc(ft_strlen(str) + 1)))
		return (NULL);
	ft_strlcpy(result, str, ft_strlen(str) + 1);
	return (result);
}

char		*ft_strldup(const char *str, int len)
{
	char	*result;

	if (!(result = malloc(len + 1)))
		return (NULL);
	ft_strlcpy(result, str, len + 1);
	result[len - 1] = '\0';
	return (result);
}

char		**ft_split_two(char *str, char c)
{
	int		count;
	char	**result;
	int		i;
	int		point;

	i = 0;
	if (str == NULL)
		return (NULL);
	count = 2;
	if ((point = ft_strchr(str,c)) == -1)
		count = 1;
	if (!(result = malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	if (count == 1)
	{
		result[0] = ft_strdup(str);
		result[1] = NULL;
		return (result);
	}
	point++;
	result[0] = ft_strldup(str,point);
	result[1] = ft_strdup(str + point);
	result[2] = NULL;
	return (result);
}

char		**ft_one_str_arr(const char *str)
{
	char	**result;

	if (!(result = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	result[0] = ft_strdup(str);
	result[1]= NULL;
	return (result);
}