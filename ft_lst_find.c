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


int is_valid_key(char *target)
{
	int i = -1;
	if(target[0]>= '0' && target[0]<= '9' )
		return 0;
	while(target[++i] && target[i] != '=')
		if(!(target[i]>= '0' && target[i] <= '9' || target[i]>= 'a' && target[i] <= 'z' || target[i]>= 'A' && target[i] <= 'Z' || target[i]>= '_'))
				return 0;
	return 1;
}

t_list		*find_lst_by_key(t_deck * deck, char *key)
{
	t_list	*temp;
	char	**list_data;
	temp = deck->head->next;

	while (temp != deck->tail)
	{
		if(ft_strchr(key,'=') > 0)
			list_data = ft_split(temp->content, '=');
		else
			list_data = ft_one_str_arr(temp->content);
			
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

char		*find_value_by_key(t_deck * deck, char *key)
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
			free_str_array(list_data);
			break;
		}
		temp = temp->next;
		free_str_array(list_data);
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
