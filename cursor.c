#include "minishell.h"
void get_cursor_position(int *h, int *v)
{
    int a = 0;
    int i = 0;
    char buf[255];
    int ret;
    int temp;

    write(0, "\033[6n", 4); //report cursor location
    ret = read(0, buf, 254);
    buf[ret] = '\0';
    while ((buf[i] < '0' || buf[i] > '9') && buf[i + 1] != ';')
        ++i;
    *v = atoi(buf + i) - 1;
    while (buf[i] != ';')
        ++i;
    *h = atoi(buf + i + 1) - 1;
}

void move_cursor_left(int *h, int *v, char *cm, int *i)
{
    if ((*i) <= 0)
        return;
    if (*h < HEADER_OFFSET)
        return;
    --(*h);
    (*i)--;
    tputs(tgoto(cm, *h, *v), 1, ft_write_ch);
}

void move_cursor_right(int *h, int *v, char *cm, int *i, int max)
{
    if (*i >= max)
        return;
    ++(*h);
    (*i)++;
    tputs(tgoto(cm, *h, *v), 1, ft_write_ch);
}

void delete_end(int *h, int *v, char *cm, char *ec, int *i, int *max)
{
    if ((*i) < 0)
        return;
    if (*h >= HEADER_OFFSET)
    {
        (*i)--;
        (*max)--;
        tputs(tgoto(cm, --(*h), *v), 1, ft_write_ch);
        tputs(ec, 1, ft_write_ch);
    }
}

void push_new(int *h, int *v, char *cm, char *ce, char * buf)
{
	tputs(tgoto(cm, HEADER_OFFSET - 1, *v), 1, ft_write_ch);
	tputs(ce, 1, ft_write_ch);
    ft_write(buf);
	tputs(tgoto(cm, ++(*h), *v), 1, ft_write_ch);
}


void check_cursor(t_cursor *cursor, char * buf, int *i)
{
			if (cursor->c == LEFT)
				move_cursor_left(&cursor->h, &cursor->v, cursor->cm, i);
			else if (cursor->c == RIGHT)
				move_cursor_right(&cursor->h, &cursor->v, cursor->cm, i, cursor->max);
			if (cursor->c == UP)
			{
				if (cursor->cur_history->pre != cursor->history->head)
				{
					cursor->cur_history = cursor->cur_history->pre;
					cursor->h = ft_strlen(cursor->cur_history->content) ;
					*i = cursor->h;
					cursor->max = cursor->h;
					ft_strlcpy(buf, cursor->cur_history->content, cursor->h + 1);
					cursor->h += HEADER_OFFSET - 2;
					push_new(&cursor->h, &cursor->v, cursor->cm, cursor->ce, buf);
				}
			}
			else if (cursor->c == DOWN)
			{

				if (cursor->cur_history->next != cursor->history->tail)
				{
					cursor->cur_history = cursor->cur_history->next;
					cursor->h = ft_strlen(cursor->cur_history->content) ;

					*i = cursor->h;
					cursor->max = cursor->h;
					ft_strlcpy(buf, cursor->cur_history->content, cursor->h + 1);

					cursor->h += HEADER_OFFSET - 2;
					push_new(&cursor->h, &cursor->v, cursor->cm, cursor->ce, buf);
				}
				//	write(1, "RIGHT",5);
			}
			else if (cursor->c == BACKSPACE)
			{

				if (*i == cursor->max)
				{
					buf[*i - 1] = '\0';
				}
				else if (*i >= 0)
					remove_char_in_str(buf, *i - 1);
				delete_end(&cursor->h, &cursor->v, cursor->cm, cursor->ec, i, &cursor->max);

				//write(1, "BACKSPACE",9);
			}
}