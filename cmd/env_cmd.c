/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:48:03 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:51:58 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_rm_env(t_deck *env, t_deck *export, char *target)
{
	ft_lstdelone(find_lst_by_key(env, target));
	ft_lstdelone(find_lst_by_key(export, target));
}

void		ft_print_all_export(t_datas datas)
{
	t_list	*temp;
	char	*str;
	int		i;
	int		len;

	temp = datas.export_list->head->next;
	while (temp != datas.export_list->tail)
	{
		i = -1;
		str = temp->content;
		len = ft_strlen(str);
		write(datas.fd.write, "declare -x ", 11);
		while (str[++i] && str[i] != '=')
			;
		write(datas.fd.write, str, i);
		if (str[i] == '=')
		{
			write(datas.fd.write, str + i++, 1);
			write(datas.fd.write, "\"", 1);
			write(datas.fd.write, str + i, len - i);
			write(datas.fd.write, "\"", 1);
		}
		write(datas.fd.write, "\n", 1);
		temp = temp->next;
	}
}

void		ft_add_export(t_deck *deck, char *target)
{
	char	**data;
	t_list	*inlist;

	if (ft_strchr(target, '=') < 0)
		data = ft_one_str_arr(target);
	else
		data = ft_split_two(target, '=');
	inlist = find_lst_by_key(deck, data[0]);
	if (!is_valid_key(target))
		return ;
	if (inlist == NULL)
	{
		inlist = ft_new_list(ft_strdup(target));
		ft_lstadd_inorder(deck, inlist);
	}
	else
		inlist->content = ft_strdup(target);
	free_str_array(data);
}

void		add_lst_export_env(t_deck *env, t_deck *export,
				char **data, char *target)
{
	t_list	*inlist;

	inlist = NULL;
	inlist = find_lst_by_key(env, data[0]);
	if (inlist == NULL)
	{
		ft_lstadd(env, ft_new_list(target));
		ft_add_export(export, target);
	}
	else
		inlist->content = ft_strdup(target);
}

void		ft_export_env(t_datas *datas, char **argv, char *target)
{
	char	**split;
	int		count;
	t_list	*inlist;

	split = ft_split_two(target, '=');
	count = -1;
	if (target == NULL)
		ft_print_all_export(*datas);
	else if (!is_valid_key(target))
	{
		print_export_err(datas->ori_fd.write, argv);
		datas->status = 1;
	}
	else
	{
		while (split[++count])
			;
		if (count > 1)
			add_lst_export_env(datas->env_list, datas->export_list,
					split, target);
		ft_add_export(datas->export_list, target);
	}
	free_str_array(split);
}
