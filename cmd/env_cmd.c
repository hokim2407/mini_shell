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

void		ft_rm_env(t_datas *datas, char *target)
{
	if (!is_valid_key(target) || target[0] == '=')
	{
		print_export_err(datas->ori_fd.write, "unset", target);
		datas->status = 1;
		return ;
	}
	ft_lstdelone(find_lst_by_key(datas->env_list, target));
	ft_lstdelone(find_lst_by_key(datas->export_list, target));
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

void		ft_push_export(t_deck *deck, char **data, char *target)
{
	t_list	*inlist;

	inlist = NULL;
	inlist = find_lst_by_key(deck, data[0]);
	if (inlist == NULL)
		ft_lstadd_inorder(deck, ft_new_list(target));
	else if (data[1] != NULL)
	{
		free(inlist->content);
		inlist->content = ft_strdup(target);
	}
}

void		ft_push_env(t_deck *env,
				char *key, char *target)
{
	t_list	*inlist;
	int		is_add;

	inlist = NULL;
	inlist = find_lst_by_key(env, key);
	is_add = (key[ft_strlen(key)-1] == '+');
	if(is_add)
		key[ft_strlen(key)-1] = '\0';
	if (inlist == NULL)
		ft_lstadd(env, ft_new_list(target));
	else
	{
		free(inlist->content);
		inlist->content = ft_strdup(target);
	}
	if (is_add)
		key[ft_strlen(key) - 1] = '+';
}

// void		ft_add_env(t_datas *datas, char *key)
// {
// 	t_list	*inlist;
// 	int		is_add;

// 	inlist = NULL;
// 	inlist = find_lst_by_key(datas->env_list, key);
// 	is_add = (key[ft_strlen(key)-1] == '+');
// 	if(is_add)
// 		key[ft_strlen(key)-1] = '\0';
// 	if (inlist == NULL)
// 		ft_lstadd(env, ft_new_list(target));
// 	else
// 	{
// 		free(inlist->content);
// 		inlist->content = ft_strdup(target);
// 	}
// 	if (is_add)
// 		key[ft_strlen(key) - 1] = '+';
// }

void		ft_export_env(t_datas *datas, char **argv, char *target)
{
	char	**split;
	int		count;

	split = ft_split_two(target, '=');
	count = -1;
	if (!is_valid_key(target) || target[0] == '=')
	{
		print_export_err(datas->ori_fd.write, argv[0], target);
		datas->status = 1;
	}
	else
	{
		while (split[++count])
			;
		if (count > 1)
			ft_push_env(datas->env_list, split[0], target);
		ft_push_export(datas->export_list, split, target);
	}
	free_str_array(split);
}
