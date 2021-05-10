/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:55:36 by hokim             #+#    #+#             */
/*   Updated: 2021/05/10 12:55:37 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_sig_end;

void			sig_ft(int signum)
{
	if (SIGINT == signum)
	{
		write(1, "\n", 2);
		write(1, HEADER, ft_strlen(HEADER));
		g_sig_end = 'c';
	}
	else if (SIGQUIT == signum)
		;
}

void			sig_ign(void)
{
	write(1, "\n", 2);
}

void			sig_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
