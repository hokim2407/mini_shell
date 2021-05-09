/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:10:52 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/09 17:10:58 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*ft_new_list(void *value)
{
	t_list	*result;

	result = malloc(sizeof(t_list));
	result->pre = NULL;
	result->content = NULL;
	if (value != NULL)
		result->content = ft_strdup((char *)value);
	result->next = NULL;
	return (result);
}

t_deck		*ft_new_deck(void)
{
	t_deck	*result;

	result = malloc(sizeof(t_deck));
	result->head = ft_new_list(NULL);
	result->tail = ft_new_list(NULL);
	result->tail->pre = result->head;
	result->head->next = result->tail;
	return (result);
}

t_deck		*array_to_list(char **envv, int is_inorder)
{
	t_deck	*result;
	int		i;

	result = ft_new_deck();
	i = -1;
	while (envv[++i])
	{
		if (is_inorder)
			ft_lstadd_inorder(result, ft_new_list(envv[i]));
		else
			ft_lstadd(result, ft_new_list(envv[i]));
	}
	return (result);
}

void		ft_lstdelone(t_list *one)
{
	if (one == NULL || one->pre == NULL || one->next == NULL)
		return ;
	one->pre->next = one->next;
	one->next->pre = one->pre;
	free(one);
}
