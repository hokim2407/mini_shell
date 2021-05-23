/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:00:06 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/23 20:52:38 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*get_env_in_cmd(char *str, int *start, int *len)
{
	char	*result;
	int		chr;
	int		i;

	chr = find_outquate_sign(str, *start);
	*start = chr;
	if (chr == -1)
		return (NULL);
	result = malloc(ft_strlen(str) - chr + 1);
	i = 0;
	chr += 1;
	while (str[chr] &&
		((str[chr] >= '0' && str[chr] <= '9') ||
		(str[chr] >= 'a' && str[chr] <= 'z') ||
		(str[chr] >= 'A' && str[chr] <= 'Z') ||
		str[chr] == '_'))
	{
		result[i++] = str[chr++];
	}
	*len = i;
	result[i] = '\0';
	return (result);
}

void		env_to_value(char **str, t_env env_data, int index, int start)
{
	char	*result;

	env_data.val_len = ft_strlen(env_data.value);
	result = malloc(ft_strlen(str[index]) + env_data.val_len + 1);
	ft_strlcpy(result, str[index], start + 1);
	ft_strlcpy(result + start, env_data.value, env_data.val_len + 1);
	ft_strlcpy(result + start + env_data.val_len,
		str[index] + start + env_data.key_len + 1,
		ft_strlen(str[index]));
	free(str[index]);
	str[index] = result;
}

int			change_env_extra_cases(char **str, int start, int status, int i)
{
	t_env	env_data;

	env_data.key_len = 1;
	if (start > -1 && str[i][start] == '$' && str[i][start + 1] == '?')
	{
		env_data.value = ft_itoa(status);
		env_data.val_len = ft_strlen(env_data.value);
		env_to_value(str, env_data, i, start);
		free(env_data.value);
	}
	else if (start > -1 && str[i][start] == '$' &&
		str[i][start + 1] >= '0' && str[i][start + 1] <= '9')
	{
		env_data.value = "";
		env_data.val_len = 0;
		env_to_value(str, env_data, i, start);
	}
	else if (start > -1 && str[i][start] == '$' && str[i][start + 1] != '_' &&
		!((str[i][start + 1] >= '0' && str[i][start + 1] <= '9') ||
		(str[i][start + 1] >= 'a' && str[i][start + 1] <= 'z') ||
		(str[i][start + 1] >= 'A' && str[i][start + 1] <= 'Z')))
		;
	else
		return (1);
	return (0);
}

int			change_env_to_value(t_datas *datas, char **str, int i, int start)
{
	t_env	env_data;

	env_data.key = get_env_in_cmd(str[i], &start, &env_data.key_len);
	if (start < 0)
		return (ft_strlen(str[i]));
	if (!change_env_extra_cases(str, start, datas->status, i))
	{
		free(env_data.key);
		return (start);
	}
	if (env_data.key == NULL || start < 0)
		return (0);
	env_data.value = find_value_by_key(datas->env_list, env_data.key);
	if (env_data.value == NULL && get_quato(str[i], start) != 1)
	{
		rm_chars_in_str(str[i], start, env_data.key_len);
		if (str[i][0] == '\0')
			pull_back_strs(str, i);
	}
	else if (get_quato(str[i], start) != 1)
		env_to_value(str, env_data, i, start);
	free(env_data.value);
	free(env_data.key);
	return (start);
}

void		check_env_in_cmd(t_datas *datas, char **cmds)
{
	int		index;
	int		start;

	if (cmds == NULL)
		return ;
	index = -1;
	while (cmds[++index])
	{
		start = 0;
		while (start < ft_strlen(cmds[index]))
			start = change_env_to_value(datas, cmds, index, start) + 1;
	}
}
