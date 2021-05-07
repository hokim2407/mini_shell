
#include "minishell.h"

void		ft_lstadd(t_deck * deck, t_list *new_lst)
{
	if (new_lst == NULL)
		return ;
        
	new_lst->pre = deck->tail->pre;
	new_lst->next = deck->tail;
	deck->tail->pre->next = new_lst;
	deck->tail->pre = new_lst;
}

void		ft_lstadd_between(t_list *front_lst, t_list *new_lst, t_list *next_lst)
{
	front_lst->next = new_lst;
	new_lst->pre = front_lst;
	next_lst->pre = new_lst;
	new_lst->next = next_lst;
}

void ft_lstadd_inorder(t_deck * deck, t_list *lst)
{
    int deck_count;
    t_list *temp;
    
    deck_count = count_deck(deck);
    temp = deck->head->next;
    if (deck_count == 0)
    {
        ft_lstadd(deck, lst);
        return;
    } 
    while (temp != deck->tail && ft_strcmp(temp->content,lst->content) < 0)
         temp = temp->next;
    ft_lstadd_between(temp->pre, lst, temp); 
      
}
