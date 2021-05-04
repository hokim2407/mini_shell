
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

int     has_char(char * str, char c)
{
    int i = -1;

    while(str[++i])
    {
        if(str[i]==c)
        return 1;
    }
    return 0;
}


void ft_lstadd_inorder(t_deck * deck, t_list *lst)
{
    int deck_count = count_deck(deck);

    t_list *temp = deck->head->next;
    int i = 0;
    if (deck_count == 0)
    {
        ft_lstadd(deck, lst);
        return;
    } 
    while (temp != deck->tail && ft_strcmp(temp->content,lst->content) < 0)
         temp = temp->next;
        ft_lst_import(temp->pre, lst, temp); 
      
}

void ft_add_export(t_deck * deck, char *target)
{
	char **data = ft_split_two(target, '=');

		
	if(!is_valid_key(target))
	{
		return;
	}

		t_list *inlist = ft_lstfind(deck, data[0]);
		if (inlist == NULL)
			ft_lstadd_inorder(deck, ft_new_list(NULL,target,NULL));
		else
			inlist->content = target;

}


t_deck *  ft_make_export_list(char **target)
{
	t_deck	*result;

	int i = -1;
	result = ft_new_deck();
	while(target[++i])
	{
            ft_add_export(result, target[i]);
	}
    return result;
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
		printf("Wrong key\n");
		return;
	}
    if(!has_char(target,'='))
    {
        ft_add_export(export, target);
        return;
    }
	while (data[++count])
		;
	if (count > 1)
	{
		t_list *inlist = ft_lstfind(env, data[0]);
		if (inlist == NULL)
			{
                ft_lstadd(env, ft_new_list(NULL,target,NULL));
                ft_add_export(export, target);
            }
		else
			{
                inlist->content = target;
                ft_lstfind(export, data[0])->content = target;
            }
	}
}