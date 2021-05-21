/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:51:13 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:51:15 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*cut_back_until(char *str, char c)
{
	int		i;

	i = ft_strlen(str);
	while (str[--i] != c)
		str[i] = '\0';
	str[i] = '\0';
	return (str);
}

char		*add_back(char *str, char *word)
{
	int		i;
	int		j;

	i = ft_strlen(str);
	j = -1;
	str[i++] = '/';
	while (word[++j])
		str[i++] = word[j];
	str[i] = '\0';
	return (str);
}

char		*get_abs_path(char *original)
{
	char	buf[256];
	char	*abs_path;
	int		count;
	char	**input_path;

	count = -1;
	getcwd(buf, 256);
	abs_path = malloc(ft_strlen(buf) + ft_strlen(original) + 2);
	ft_strlcpy(abs_path, buf, ft_strlen(buf) + 1);
	input_path = ft_split(original, '/');
	while (input_path[++count])
	{
		if (!ft_strcmp(input_path[count], ".."))
			abs_path = cut_back_until(abs_path, '/');
		else if (ft_strcmp(input_path[count], ".") != 0)
			abs_path = add_back(abs_path, input_path[count]);
	}
	return (abs_path);
}

void		pull_back_strs(char **strs, int i)
{
	char	*temp;

	temp = strs[i];
	while (strs[i])
	{
		*(strs + i) = *(strs + i + 1);
		i++;
	}
	free(temp);
}
