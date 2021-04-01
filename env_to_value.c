#include "minishell.h"

char		*get_env_in_cmd(char *str, int *start, int *len)
{
	char	*result;
	int		chr;
	int		i;

	chr = ft_strchr(str, '$');
	if (chr == -1)
		return NULL;
	result = malloc(ft_strlen(str) - chr + 1);
	i = 0;
	*start = chr;
	chr += 1;
	while (str[chr] >= '0' && str[chr] <= '9' ||
		str[chr] >= 'a' && str[chr] <= 'z' ||
		str[chr] >= 'A' && str[chr] <= 'Z' ||
		str[chr] == '_' )
	{
		result[i++] = str[chr++];
	}
	*len = i;
	result[i] = '\0';
    return result;
}

void		change_env_to_value(char **str, t_deck *env)
{
	int		start;
	t_env	env_data;
    char	*result;
	int 	index;
	
	index = -1;
	while (str[++index])
	{
		env_data.key = get_env_in_cmd(str[index], &start, &env_data.key_len);
		if(env_data.key == NULL || (start > 0 && str[index][start-1] == '\''))
			continue ;
		env_data.value = find_value_in_list(env, env_data.key);
		if(env_data.value == NULL)
		{
			ft_strlcpy(result , str[index], start + 1);
			ft_strlcpy(result + start, str[index]+ start + env_data.key_len + 1, ft_strlen(str[index]));
			str[index] =result;
			continue;
		}
		env_data.val_len = ft_strlen(env_data.value);
		result = malloc(ft_strlen(str[index]) + env_data.val_len + 1);
		ft_strlcpy(result , str[index], start + 1);
		ft_strlcpy(result + start , env_data.value, env_data.val_len + 1);
		ft_strlcpy(result + start + env_data.val_len , str[index]+ start + env_data.key_len + 1, ft_strlen(str[index]));
		str[index] =result;
	}
}

void		check_env_in_cmd(char **cmds,t_deck *env)
{
	int		len;
	int		chr;

	if (cmds == NULL)
		return ;
	change_env_to_value(cmds,  env);
	int i = -1;
}