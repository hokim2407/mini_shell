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

#include "minishell.h"

void		ft_rm_env(t_deck *env, t_deck *export, char *target)
{
	ft_lstdelone(find_lst_by_key(env, target));
	ft_lstdelone(find_lst_by_key(export, target));
}

void		ft_print_all_export(t_deck deck)
{
	t_list	*temp;
	char	*str;
	int		i;
	int		len;

	temp = deck.head->next;
	while (temp != deck.tail)
	{
		i = -1;
		str = temp->content;
		len = ft_strlen(str);
		write(1, "declare -x ", 11);
		while (str[++i] && str[i] != '=')
			;
		write(1, str, i);
		if (str[i] == '=')
		{
			write(1, str + i++, 1);
			write(1, "\"", 1);
			write(1, str + i, len - i);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
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
	t_list *inlist;

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


int				print_env_err(int fd, char **argv)
{
	int len;

	len = -1;
	while (argv[++len])
		;
	write(fd, argv[0], ft_strlen(argv[0]));
	write(fd, ": ", 2);
	write(fd, argv[len - 1], ft_strlen(argv[len - 1]));
	write(fd, ": ", 2);
	write(fd, "No such file or directory", ft_strlen("No such file or directory"));
	write(fd, "\n", 1);
	return (1);
}


int				print_export_err(int fd, char **argv)
{
	int len;

	len = -1;
	while (argv[++len])
		;
	write(fd, "minishell: ", 11);
	write(fd, argv[0], ft_strlen(argv[0]));
	write(fd, ": `", 3);
	write(fd, argv[len - 1], ft_strlen(argv[len - 1]));
	write(fd, "\': ", 3);
	write(fd, "not a valid identifier", ft_strlen("not a valid identifier"));
	write(fd, "\n", 1);

	return (1);
}

void		ft_export_env(t_datas * datas,char **argv, char *target)
{
	char	**split;
	int		count;
	t_list	*inlist;

	split = ft_split_two(target, '=');
	count = -1;
	if (target == NULL)
		ft_print_all_export(*(datas->export_list));
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
			add_lst_export_env(datas->env_list, datas->export_list, split, target);
		ft_add_export(datas->export_list, target);
	}
	free_str_array(split);
}
