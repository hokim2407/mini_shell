/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:45:52 by hokim             #+#    #+#             */
/*   Updated: 2021/03/25 10:54:39 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*ft_new_list(t_list * pre, void* value, t_list * next)
{
	t_list	*result;

	result = malloc(sizeof(t_list));
	result->pre = pre;
	result->content = value;
	result->next = next;

	return (result);
}


t_deck		*ft_new_deck()
{
	t_deck	*result;

	result = malloc(sizeof(t_deck));
	result->head = ft_new_list(NULL, NULL, NULL);
	result->tail = ft_new_list(result->head, NULL, NULL);
	result->head->next = result->tail;
	return (result);
}

t_deck		*array_to_list(char **envv)
{
	t_deck	*result;
	int i;

	result = ft_new_deck();
	i = -1;
	while (envv[++i])
	{
		ft_lstadd(result, ft_new_list(NULL, envv[i], NULL));
	}
	return (result);
}

void		ft_lstdelone(t_list *one)
{
	if(one == NULL || one->pre == NULL || one->next == NULL)
		return;
	one->pre->next = one->next;
	one->next->pre = one->pre;
	free(one);
}

void		ft_lstadd(t_deck * deck, t_list *new_lst)
{
	t_list	*tail;

	if (new_lst == NULL)
		return ;
	tail = deck->tail;
	new_lst->pre = tail->pre;
	new_lst->next = tail;
	tail->pre->next = new_lst;
	tail->pre = new_lst;
}


void		ft_lst_import(t_list *front_lst, t_list *new_lst, t_list *next_lst)
{
	front_lst->next = new_lst;
	new_lst->pre = front_lst;
	next_lst->pre = new_lst;
	new_lst->next = next_lst;
}

t_list		*ft_lstfind(t_deck * deck, char *key)
{
	t_list	*temp;
	char	**list_data;

	temp = deck->head->next;
	while (temp != deck->tail)
	{
		list_data = ft_split(temp->content, '=');
		if (!ft_strcmp(list_data[0], key))
		{
			free_str_array(list_data);
			return temp;
		}
		temp = temp->next;
		free_str_array(list_data);
	}
	return (NULL);
}

char		*find_value_in_list(t_deck * deck, char *key)
{
	t_list	*temp;
	char	**list_data;
	char	*result;
	result = NULL;
	temp = deck->head->next;
	while (temp != deck->tail)
	{
		list_data = ft_split_two(temp->content, '=');
		if (!ft_strcmp(list_data[0], key))
		{
			result = ft_strdup(list_data[1]);
			break ;
		}
		temp = temp->next;
	}
	return (result);
}

int		count_deck(t_deck * deck)
{
	t_list	*temp;
	int count = 0;
	temp = deck->head->next;
	while (temp != deck->tail)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
