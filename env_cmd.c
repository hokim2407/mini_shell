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

void ft_rm_env(t_deck * deck, char *target)
{
	ft_lstdelone(find_lst_by_key(deck, target));
}

void ft_print_all_export(t_deck deck)
{
	t_list *temp = deck.head->next;
    char * str;
    int i;
    int len;
	while (temp!= deck.tail)
	{
        i = 0;
        str =  temp->content;
        len = ft_strlen(str);
        while( str[i++] && str[i]!= '=')
        ;
		write(1,str, i + 1);
        if(str[i]== '=')
         {
            write(1, "\"", 1);
            write(1, str + i + 1, len - i);
            write(1, "\"", 1);
         }

        write(1, "\n", 1);
		temp = temp->next;
	}
}


void ft_add_export(t_deck * deck, char *target)
{
    char **data = ft_split_two(target, '=');

    if (!is_valid_key(target))
        return;
    t_list *inlist = find_lst_by_key(deck, data[0]);
    if (inlist == NULL)
        ft_lstadd_inorder(deck, ft_new_list(target));
    else
        inlist->content = target;
}

void ft_export_env(t_deck * env,t_deck * export, char *target)
{
	char **data = ft_split_two(target, '=');
	int count = -1;
	if(target == NULL)
    {
        ft_print_all_export(*export);
        return;
    }
 
	if(!is_valid_key(target))
	{
		printf("not a valid identifier\n");
		return;
	}
    if(ft_strchr(target,'=') < 0)
    {
        ft_add_export(export, target);
        return;
    }
	while (data[++count])
		;
	if (count > 1)
	{
		t_list *inlist = find_lst_by_key(env, data[0]);
		if (inlist == NULL)
			{
                ft_lstadd(env, ft_new_list(target));
                ft_add_export(export, target);
            }
		else
			{
                inlist->content = target;
                find_lst_by_key(export, data[0])->content = target;
            }
	}
}