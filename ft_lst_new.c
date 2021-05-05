#include "minishell.h"

t_list		*ft_new_list(void* value)
{
	t_list	*result;

	result = malloc(sizeof(t_list));
	result->pre = NULL;
	result->content = value;
	result->next = NULL;

	return (result);
}


t_deck		*ft_new_deck()
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
	int i;

	result = ft_new_deck();
	i = -1;
	while (envv[++i])
	{
        if(is_inorder)
            ft_lstadd_inorder(result, ft_new_list(envv[i]));
        else
		    ft_lstadd(result, ft_new_list(envv[i]));
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

