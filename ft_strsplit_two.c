/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:49:26 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:49:28 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if ((point = ft_strchr(str, c)) == -1)
		count = 1;
	if (!(result = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	if (count == 1)
	{
		result[0] = ft_strdup(str);
		result[1] = NULL;
		return (result);
	}
	point++;
	result[0] = ft_strldup(str, point);
	result[1] = ft_strdup(str + point);
	result[2] = NULL;
	return (result);
}

char		**ft_one_str_arr(const char *str)
{
	char	**result;

	if (!(result = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	result[0] = ft_strdup(str);
	result[1] = NULL;
	return (result);
}

void		rm_chars_in_str(char *buf, int start, int len)
{
	int		i;

	i = start - 1;
	while (buf[++i + len + 1])
		buf[i] = buf[i + len + 1];
	buf[i] = '\0';
}
