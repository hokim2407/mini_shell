/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:48:03 by hokim             #+#    #+#             */
/*   Updated: 2021/05/23 20:54:28 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_rm_env(t_datas *datas, char *target)
{
	t_list	*data;
	int		chr;
	int		i;

	i = -1;
	if (!is_valid_key(target) || target[0] == '='
		|| ft_strchr(target, '=') > -1)
	{
		print_export_err(datas->ori_fd.err, &(datas->status), "unset", target);
		return ;
	}
	data = find_lst_by_key(datas->env_list, target);
	while (++i < 2)
	{
		if (data != NULL)
		{
			data->is_unseted = 1;
			chr = ft_strchr((char *)data->content, '=');
			if (chr > -1)
				((char *)data->content)[chr] = '\0';
		}
		data = find_lst_by_key(datas->export_list, target);
	}
}

void		ft_print_all_export(t_datas datas)
{
	t_list	*temp;
	char	*str;
	int		i;

	temp = datas.export_list->head->next;
	while (temp != datas.export_list->tail)
	{
		if (!temp->is_unseted)
		{
			str = temp->content;
			i = ft_strchr(str, '=');
			i = (i < 0) ? ft_strlen(str) : i;
			write(datas.fd.write, "declare -x ", 11);
			write(datas.fd.write, str, i);
			if (str[i] == '=')
			{
				write(datas.fd.write, str + i++, 1);
				write(datas.fd.write, "\"", 1);
				write(datas.fd.write, str + i, ft_strlen(str) - i);
				write(datas.fd.write, "\"", 1);
			}
			write(datas.fd.write, "\n", 1);
		}
		temp = temp->next;
	}
}

void		ft_push_export(t_deck *deck, char **data, char *target, int is_add)
{
	t_list	*inlist;
	char	*temp;

	inlist = find_lst_by_key(deck, data[0]);
	if (inlist == NULL)
		ft_lstadd_inorder(deck, ft_new_list(target));
	else if (data[1] != NULL)
	{
		temp = inlist->content;
		if (is_add)
		{
			if (ft_strchr(temp, '=') < 0)
			{
				inlist->content = ft_strjoin(temp, "=");
				free(temp);
				temp = inlist->content;
			}
			inlist->content = ft_strjoin(temp, data[1]);
		}
		else
			inlist->content = ft_strdup(target);
		free(temp);
	}
	else
		inlist->is_unseted = 0;
}

void		ft_push_env(t_deck *env,
				char **data, char *target, int is_add)
{
	t_list	*inlist;
	char	*temp;
	int		len;

	len = ft_strlen(data[0]);
	inlist = find_lst_by_key(env, data[0]);
	if (inlist == NULL)
		ft_lstadd(env, ft_new_list(target));
	else
	{
		temp = inlist->content;
		if (is_add)
			inlist->content = ft_strjoin(temp, data[1]);
		else
			inlist->content = ft_strdup(target);
		inlist->is_unseted = 0;
		free(temp);
	}
}

void		ft_export_env(t_datas *datas, char **argv, char *target)
{
	char	**split;
	int		count;
	int		is_add;

	split = ft_split_two(target, '=');
	count = -1;
	if (!is_valid_key(target) || target[0] == '=')
		print_export_err(datas->ori_fd.err, &(datas->status), argv[0], target);
	else
	{
		is_add = (split[0][ft_strlen(split[0]) - 1] == '+');
		if (is_add)
		{
			split[0][ft_strlen(split[0]) - 1] = '\0';
			rm_chars_in_str(target, ft_strchr(target, '+'), 0);
		}
		while (split[++count])
			;
		if (count > 1)
			ft_push_env(datas->env_list, split, target, is_add);
		ft_push_export(datas->export_list, split, target, is_add);
	}
	free_str_array(split);
}
