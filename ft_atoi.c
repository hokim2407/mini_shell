/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:46:21 by hokim             #+#    #+#             */
/*   Updated: 2021/04/02 12:50:25 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_atoi(const char *str)
{
	int		value;
	int		flag;
	int		i;

	i = 0;
	value = 0;
	flag = 1;
	while ((*(str + i) > 8 && *(str + i) < 14) || *(str + i) == 32)
		i++;
	if (*(str + i) == '+')
		i++;
	else if (*(str + i) == '-')
	{
		i++;
		flag *= (-1);
	}
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		value = value * 10 + *(str + i) - '0';
		i++;
	}
	return (int)value * flag;
}
