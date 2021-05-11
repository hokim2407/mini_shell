/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:50:09 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:50:11 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		move_cursor_horizontal(t_cursor *cursor, int *i, int is_left)
{
	if (is_left)
	{
		if (*i <= 0 || cursor->h < cursor->term_offset)
			return ;
		--(cursor->h);
		(*i)--;
	}
	else
	{
		if (*i >= cursor->max)
			return ;
		++(cursor->h);
		(*i)++;
	}
	tputs(tgoto(cursor->cm, (cursor->h), (cursor->v)), 1, ft_write_ch);
}

void		move_cursor_vertital(t_cursor *cursor, char *buf, int *i, int is_up)
{
	if (is_up && cursor->cur_history == cursor->history->head ||
		is_up && cursor->cur_history->pre == cursor->history->head)
		return ;
	if (!is_up && cursor->cur_history->next == cursor->history->tail ||
		!is_up && cursor->cur_history == cursor->history->tail)
	{
		if (cursor->cur_history->next == cursor->history->tail)
			cursor->cur_history = cursor->history->tail;
		*i = 0;
		cursor->max = 0;
		buf[0] = '\0';
		cursor->h = ft_strlen(HEADER) - 1;
		push_new(cursor, buf);
		return ;
	}
	if (is_up)
		cursor->cur_history = cursor->cur_history->pre;
	else if (!is_up)
		cursor->cur_history = cursor->cur_history->next;
	cursor->h = ft_strlen(cursor->cur_history->content);
	*i = cursor->h;
	cursor->max = cursor->h;
	ft_strlcpy(buf, cursor->cur_history->content, cursor->h + 1);
	cursor->h += cursor->term_offset - 1;
	push_new(cursor, buf);
}

void		delete_end(t_cursor *cursor, int *i)
{
	if ((*i) < 0)
		return ;
	if (cursor->h > cursor->term_offset)
	{
		(*i)--;
		cursor->max--;
		tputs(tgoto(cursor->cm, --(cursor->h), cursor->v), 1, ft_write_ch);
		tputs(cursor->dc, 1, ft_write_ch);
	}
}

void		push_new(t_cursor *cursor, char *buf)
{
	tputs(tgoto(cursor->cm, cursor->term_offset, cursor->v), 1, ft_write_ch);
	tputs(cursor->ce, 1, ft_write_ch);
	ft_write(buf);
	tputs(tgoto(cursor->cm, ++(cursor->h), cursor->v), 1, ft_write_ch);
}

void		check_cursor(t_cursor *cursor, char *buf, int *i)
{
	get_cursor_position(&(cursor->h), &(cursor->v));
	if (cursor->c == LEFT)
		move_cursor_horizontal(cursor, i, 1);
	else if (cursor->c == RIGHT)
		move_cursor_horizontal(cursor, i, 0);
	if (cursor->c == UP)
		move_cursor_vertital(cursor, buf, i, 1);
	else if (cursor->c == DOWN)
		move_cursor_vertital(cursor, buf, i, 0);
	else if (cursor->c == BACKSPACE)
	{
		if (*i == cursor->max && *i > 0)
			buf[*i - 1] = '\0';
		else if (*i > 0)
			remove_char_in_str(buf, *i - 1);
		delete_end(cursor, i);
	}
}
