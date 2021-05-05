#include "minishell.h"

void rm_quato(char **buf)
{
	int i = -1;
	int j;
	int str_i;
	int quato = 0;
	char *temp;

	while (buf[++i])
	{
		temp = malloc(ft_strlen(buf[i]) + 1);
		j = -1;
		str_i = 0;
		while (buf[i][++j])
		{
			if ((quato == 1 && buf[i][j] == '\'') || (quato == 2 && buf[i][j] == '\"'))
				quato = 0;
			else if (quato == 0 && buf[i][j] == '\'')
				quato = 1;
			else if (quato == 0 && buf[i][j] == '\"')
				quato = 2;
			else
			{
				temp[str_i++] = buf[i][j] ;
			}
			temp[str_i] = '\0';
		}
		free(buf[i]);
		buf[i] = temp;
	}
}

int get_quato(char *str, int util)
{
	int quato;
	int i = -1;
	quato = 0;
	while(str[++i]  && i <= util)
	{
		if((quato == 1 && str[i] == '\'') || (quato == 2 && str[i] == '\"') )
			quato = 0;
		else if(quato == 0 && str[i] == '\'')
			quato = 1;
		else if(quato == 0 && str[i] == '\"')
			quato = 2;
	}
	return quato;
}