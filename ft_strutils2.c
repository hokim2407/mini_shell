
#include "minishell.h"

int		ft_strchr(const char *str, int value)
{
	int		i;

	i = 0;
	if (*str == '\0' && value == 0)
		return (-1);
	while (*(str + i) != '\0')
	{
		if (*(str + i) == value)
			return (i);
		i++;
	}
	if (*(str + i) == value)
		return (i);
	return (-1);
}


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

int			ft_write(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		;
	write(1, str, i);
	return 1;
}
