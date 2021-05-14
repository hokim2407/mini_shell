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

extern t_sig	g_sig;

void			sig_ft(int signum)
{
	if (SIGINT == signum)
	{
		write(1, "\n", 2);
		write(1, HEADER, ft_strlen(HEADER));
		g_sig.sig = 'c';
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

void			sig_special(int signum)
{
	if (signum == SIGINT && g_sig.is_cat)
		write(1, "\n", 1);
	if (signum == SIGQUIT && g_sig.is_cat)
		write(1, "Quit: 3\n", 10);
}
