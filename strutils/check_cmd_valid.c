/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:50:53 by hokim             #+#    #+#             */
/*   Updated: 2021/05/21 20:19:24 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char				**check_echo(char **new_argv)
{
	int				i;
	int				index;
	int				is_continued;
	char			**smaller_argv;

	i = 0;
	while (new_argv[++i])
		;
	is_continued = 0;
	smaller_argv = malloc(sizeof(char *) * i + 1);
	smaller_argv[0] = ft_strdup(new_argv[0]);
	i = 0;
	index = 1;
	while (new_argv[++i])
	{
		if ((is_n_option(new_argv[i]) && i != 1) && !is_continued)
			continue ;
		smaller_argv[index++] = ft_strdup(new_argv[i]);
		if (!is_n_option(new_argv[i]))
			is_continued = 1;
	}
	smaller_argv[index] = NULL;
	free_str_array(new_argv);
	return (smaller_argv);
}

char				**check_upper_case(char **new_argv)
{
	int				i;

	i = 0;
	while (new_argv[0][i])
	{
		if (('A' <= new_argv[0][i]) && (new_argv[0][i] <= 'Z'))
			new_argv[0][i] += 32;
		i++;
	}
	return (new_argv);
}

void				check_env_data_null_case(char **str,
							t_env env_data, int start, int *i)
{
	rm_chars_in_str(str[*i], start, env_data.key_len);
	if (ft_strlen(str[*i]) == 0)
	{
		pull_back_strs(str, *i);
		(*i)--;
	}
}

void				change_pwd_env(t_datas *datas, char *old_path)
{
	char		*temp;
	char		now_path[256];

	getcwd(now_path, 255);
	temp = ft_strjoin("OLDPWD=", old_path);
	ft_export_env(datas, NULL, temp);
	free(temp);
	temp = ft_strjoin("PWD=", now_path);
	ft_export_env(datas, NULL, temp);
	free(temp);
	free(old_path);
}
