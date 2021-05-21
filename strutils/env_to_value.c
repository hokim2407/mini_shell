/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:00:06 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/19 22:03:12 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			find_out_sign(char *str)
{
	int temp;
	int chr;

	temp = ft_strchr(str, '$');
	chr = temp;
	if (temp != -1 && get_quato(str, chr) == 1)
	{
		temp = ft_strchr(str + chr + 1, '$');
		chr += temp + 1;
	}
	if (temp == -1)
		chr = -1;
	return (chr);
}

char		*get_env_in_cmd(char *str, int *start, int *len)
{
	char	*result;
	int		chr;
	int		i;

	chr = find_out_sign(str);
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
	char *result;

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

void		change_env_to_value(char **str, t_deck *env, int status, int *i)
{
	int		start;
	t_env	env_data;

	env_data.key = get_env_in_cmd(str[*i], &start, &env_data.key_len);
	if (start > -1 && str[*i][start] == '$' && str[*i][start + 1] == '?')
	{
		env_data.key_len = 1;
		env_data.value = ft_itoa(status);
		env_data.val_len = ft_strlen(env_data.value);
		env_to_value(str, env_data, *i, start);
		return ;
	}
	if (env_data.key == NULL || start < 0)
		return ;
	env_data.value = find_value_by_key(env, env_data.key);
	if (get_quato(str[*i], start) != 1)
	{
		if (env_data.value == NULL)
			rm_chars_in_str(str[*i], start, env_data.key_len);
		else
			env_to_value(str, env_data, *i, start);
		(*i)--;
	}
	free(env_data.value);
	free(env_data.key);
}

void		check_env_in_cmd(char **cmds, t_deck *env, int status)
{
	int		index;

	if (cmds == NULL)
		return ;
	index = -1;
	while (cmds[++index])
		change_env_to_value(cmds, env, status, &index);
}
