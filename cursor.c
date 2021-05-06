#include "minishell.h"

void get_cursor_position(int *h, int *v)
{
	int a = 0;
	int i = 0;
	char buf[255];
	int ret;
	int temp;

	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while ((buf[i] < '0' || buf[i] > '9') && buf[i + 1] != ';')
		++i;
	*v = atoi(buf + i) - 1;
	while (buf[i] != ';')
		++i;
	*h = atoi(buf + i + 1) - 1;
}

void move_cursor_horizontal(t_cursor *cursor, int *i, int is_left)
{
	if (is_left)
	{
		if (*i <= 0 || cursor->h < cursor->term_offset)
			return;
		--(cursor->h);
		(*i)--;
	}
	else
	{
		if (*i >= cursor->max)
			return;
		++(cursor->h);
		(*i)++;
	}
	tputs(tgoto(cursor->cm, (cursor->h), (cursor->v)), 1, ft_write_ch);
}

void move_cursor_vertital(t_cursor *cursor, char *buf, int *i, int is_up)
{
	if(is_up && cursor->cur_history == cursor->history->head || 
		is_up && cursor->cur_history->pre == cursor->history->head|| 
		!is_up && cursor->cur_history->next == cursor->history->tail || 
		!is_up  && cursor->cur_history == cursor->history->tail)
		return ;
	if (is_up  )
		cursor->cur_history = cursor->cur_history->pre;
	else if (!is_up )
		cursor->cur_history = cursor->cur_history->next;
	cursor->h = ft_strlen(cursor->cur_history->content);
	*i = cursor->h;
	cursor->max = cursor->h;
	ft_strlcpy(buf, cursor->cur_history->content, cursor->h + 1);
	cursor->h += cursor->term_offset - 1;
	push_new(cursor, buf);
}

void delete_end(t_cursor *cursor,int *i)
{
	if ((*i) < 0)
		return;
	if (cursor->h > cursor->term_offset)
	{
		(*i)--;
		cursor->max--;
		tputs(tgoto(cursor->cm, --(cursor->h), cursor->v), 1, ft_write_ch);
		tputs(cursor->dc, 1, ft_write_ch);
	}
}

void push_new(t_cursor *cursor, char *buf)
{
	tputs(tgoto(cursor->cm, cursor->term_offset, cursor->v), 1, ft_write_ch);
	tputs(cursor->ce, 1, ft_write_ch);
	ft_write(buf);
	tputs(tgoto(cursor->cm, ++(cursor->h), cursor->v), 1, ft_write_ch);
}

void check_cursor(t_cursor *cursor, char *buf, int *i)
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
		if (*i == cursor->max && *i >0)
			buf[*i - 1] = '\0';
		else if (*i >= 0)
			remove_char_in_str(buf, *i - 1);
		delete_end(cursor, i);
	}
}