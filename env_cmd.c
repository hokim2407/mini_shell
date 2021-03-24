/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:48:03 by hokim             #+#    #+#             */
/*   Updated: 2021/03/20 16:14:34 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_print_all_deck(t_deck deck)
{
	t_list *temp = deck.head->next;
	while (temp!= deck.tail)
	{
		write(1, temp->content, ft_strlen(temp->content));
		write(1, "\n", 1);
		temp = temp->next;
	}
}

void ft_r_print_all_deck(t_deck deck)
{
	t_list *temp = deck.tail->pre;
	while (temp!= deck.head)
	{
		write(1, temp->content, ft_strlen(temp->content));
		write(1, "\n", 1);
		temp = temp->pre;
	}
}

void ft_rm_env(t_deck * deck, char *target)
{
	ft_lstdelone(ft_lstfind(deck, target));
}

void ft_add_env(t_deck * deck, char *target)
{
	char **data = ft_split_two(target, '=');
	int count = -1;
	while (data[++count])
		;
	if (count > 1)
	{
		t_list *inlist = ft_lstfind(deck, data[0]);
		if (inlist == NULL)
			ft_lstadd(deck, ft_new_list(NULL,target,NULL));
		else
			inlist->content = target;
	}
}

