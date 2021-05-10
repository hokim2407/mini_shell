/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:49:02 by hokim             #+#    #+#             */
/*   Updated: 2021/05/10 14:46:00 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				g_sig_end;

int				print_err(int fd)
{
	write(fd, strerror(errno), ft_strlen(strerror(errno)));
	write(fd, "\n", 1);
	return (1);
}

void			shell_init(t_datas *datas, t_cursor *cursor, char **envv)
{
	g_sig_end = 0;
	set_terminal(&cursor->cm, &cursor->dc, &cursor->ce);
	cursor->history = ft_new_deck();
	cursor->cur_history = cursor->history->tail;
	datas->env_list = array_to_list(envv, 0);
	datas->export_list = array_to_list(envv, 1);
	datas->envv = envv;
	datas->fd.read = 0;
	datas->fd.write = 1;
	datas->status = 0;
}

void			new_input_init(t_cursor *cursor, char *buf, int *i)
{
	set_again_terminal();
	write(1, HEADER, ft_strlen(HEADER));
	get_cursor_position(&(cursor->term_offset), &(cursor->v));
	buf[0] = '\0';
	cursor->max = 0;
	*i = 0;
	cursor->c = 0;
	signal(SIGINT, sig_ft);
	signal(SIGQUIT, sig_ft);
}

int				main(int argc, char **argv, char **envv)
{
	char		buf[4096];
	t_datas		datas;
	t_cursor	cursor;
	int			i;
	char		**blocks;

	shell_init(&datas, &cursor, envv);
	while (1)
	{
		new_input_init(&cursor, buf, &i);
		while (read(0, &cursor.c, sizeof(int)) > 0 && cursor.c != '\n')
			read_char_process(buf, &cursor, &i);
		back_terminal();
		ft_lstadd(cursor.history, ft_new_list(buf));
		cursor.cur_history = cursor.history->tail;
		if (buf[0] != '\n')
			write(1, "\n", 1);
		if (buf[0] == '\0' || buf[0] == '\n')
			continue;
		blocks = ft_split(buf, ';');
		i = -1;
		while (blocks[++i])
			pipe_process(blocks[i], &datas);
		free_str_array(blocks);
	}
}
