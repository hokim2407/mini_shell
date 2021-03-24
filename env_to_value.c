#include "minishell.h"

char		*get_only_env(char *str, int *start, int *len)
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

void		trim_side(char **str)
{
	char	*s1 = *str;
	int		len;

	len = ft_strlen(s1);
	s1[len - 1] = '\0';
	*str = ft_strdup(s1 + 1);
	free(s1);
}
void		change_env_to_value(char **str,char * s1, t_deck *env)
{
	char	*env_value;
	int		start;
	int		env_len;
	int		env_val_len;
	char	*env_key;
    char	*result;

	env_key = get_only_env(*str, &start, &env_len);
	env_value = find_lst_value(env, env_key);
	env_val_len = ft_strlen(env_value);
	result = malloc(ft_strlen(s1) + env_val_len + 1);
	int i = -1;
	while (s1[++i] && i < start)
		result[i] = s1[i];
    result[i] = 0;
	ft_strlcpy(result + i , env_value, env_val_len + 1);
    env_len++;
	while (s1[i + env_len])
	{
		result[i+ env_val_len] = s1[i + env_len];
		i++;
	}
    result[i+ env_val_len]  = '\0';
    *str =result;
}

void		check_env_in_cmd(char **str,t_deck *env)
{
	char	*s1= *str;
	int		len;
	int		chr;

	len = ft_strlen(s1);
	if (s1 == NULL)
		return ;
	if (s1[0] == '\'' && s1[len - 1] == '\'')
	{
		trim_side(str);
		return ;
	}
	if ((chr = ft_strchr(s1, '$') != -1))
		change_env_to_value(str, s1, env);
	if (s1[0] == '\"' && s1[len - 1] == '\"')
	{
		trim_side(str);
		s1 = *str;
	}
}