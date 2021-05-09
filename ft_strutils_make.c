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
