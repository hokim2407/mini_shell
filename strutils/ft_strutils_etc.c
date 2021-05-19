/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils_etc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:51:00 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:51:03 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_strcmp(char *str1, char *str2)
{
	int		i;
	int		len1;
	int		len2;

	i = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	while (i < len1 && i < len2)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int			ft_strlcmp(char *str1, char *str2, int len)
{
	int		i;
	int		len1;
	int		len2;

	i = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	while (i < len1 && i < len2 && i < len)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (i == len - 1)
		return (str1[i] - str2[i]);
	else
		return (0);
}

void		remove_char_in_str(char *buf, int nth)
{
	int		i;

	i = nth;
	while (buf[i])
	{
		buf[i] = buf[i + 1];
		i++;
	}
}

void		put_char_in_str(char *buf, char c, int nth)
{
	int		len;

	len = ft_strlen(buf) + 1;
	buf[len] = '\0';
	while (len > nth)
	{
		buf[len] = buf[len - 1];
		len--;
	}
	buf[len] = c;
}

void		free_str_array(char **str)
{
	int		i;

	if (str == NULL)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
