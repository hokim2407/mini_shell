/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:51:13 by hokim             #+#    #+#             */
/*   Updated: 2021/05/23 20:30:21 by hyerkim          ###   ########.fr       */
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

char		**change_wave_to_home(char **new_argv, t_datas *datas)
{
	int		i;
	char	*path;
	char	*temp;

	i = -1;
	path = find_value_by_key(datas->env_list, "HOME");
	while (new_argv[++i])
	{
		if (new_argv[i] && new_argv[i][0] == '~')
		{
			temp = new_argv[i];
			if (new_argv[i][1] == '\0')
				new_argv[i] = ft_strdup(path);
			else if (new_argv[i][1] == '/')
				new_argv[i] = ft_strjoin(path, new_argv[i] + 1);
			else
				continue;
			free(temp);
		}
	}
	free(path);
	return (new_argv);
}
