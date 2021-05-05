
#include "minishell.h"

int			ft_strcmp(char *str1, char *str2)
{
	int		i;
	int		len1;
	int		len2;

	i = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);

	while (i < len1 && i < len2)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int			ft_strlcmp(char *str1, char *str2, int len)
{
	int		i;
	int		len1;
	int		len2;

	i = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);

	while (i < len1 && i < len2 && i < len)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}



void remove_char_in_str(char *buf,int nth)
{
	int i = nth ;
	while(buf[i])
	{
		buf[i] = buf[i + 1];
		i++;
	}
	
}

void put_char_in_str(char *buf, char c, int nth)
{
	int len = ft_strlen(buf) + 1;
	buf[len] = '\0';
	while(len > nth)
	{
		buf[len] = buf[len - 1];
		len --;
	}
	buf[len] = c;
}
