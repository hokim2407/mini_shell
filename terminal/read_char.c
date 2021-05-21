/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 19:33:13 by hokim             #+#    #+#             */
/*   Updated: 2021/05/21 20:06:08 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern		t_sig g_sig;

void		ascii_char_process(char *buf, t_cursor *cursor, int *i)
{
	if (cursor->max < ++(*i))
	{
		buf[*i - 1] = cursor->c;
		write(1, buf + *i - 1, 1);
	}
	else
	{
		put_char_in_str(buf, cursor->c, *i - 1);
		push_new(cursor, buf);
	}
	cursor->max++;
	buf[cursor->max] = '\0';
}

void		read_char_process(char *buf, t_cursor *cursor, int *i)
{
	if (g_sig.sig == 'c')
	{
		g_sig.sig = 0;
		buf[0] = '\0';
		*i = 0;
		cursor->max = 0;
	}
	if ((cursor->c == 4 && cursor->max != 0) || cursor->c == '\t')
		return ;
	if (cursor->c == 4)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	check_cursor(cursor, buf, i);
	if (cursor->c < 127)
		ascii_char_process(buf, cursor, i);
	cursor->c = 0;
	buf[cursor->max + 1] = '\0';
}
