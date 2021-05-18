/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quato.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:50:30 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:50:44 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			get_quato(char *str, int util)
{
	int		quato;
	int		i;

	i = -1;
	quato = 0;
	while (str[++i] && i <= util)
	{
		if ((quato == 1 && str[i] == '\'') || (quato == 2 && str[i] == '\"'))
			quato = 0;
		else if (quato == 0 && str[i] == '\'')
			quato = 1;
		else if (quato == 0 && str[i] == '\"')
			quato = 2;
	}
	return (quato);
}

void		check_quato_and_cp(char *target, char *str)
{
	int		i;
	int		quato;
	int		str_i;

	quato = 0;
	i = -1;
	str_i = 0;
	while (str[++i])
	{
		if ((quato == 1 && str[i] == '\'')
			|| (quato == 2 && str[i] == '\"'))
			quato = 0;
		else if (quato == 0 && str[i] == '\'')
			quato = 1;
		else if (quato == 0 && str[i] == '\"')
			quato = 2;
		else
			target[str_i++] = str[i];
		target[str_i] = '\0';
	}
}

void		rm_quato(char **buf)
{
	int		i;
	char	*temp;

	i = -1;
	while (buf[++i])
	{
		if (buf[i][0] == '\0')
			continue;
		temp = malloc(ft_strlen(buf[i]) + 1);
		check_quato_and_cp(temp, buf[i]);
		free(buf[i]);
		buf[i] = temp;
	}
}
