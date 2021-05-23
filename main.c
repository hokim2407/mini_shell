/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:49:02 by hokim             #+#    #+#             */
/*   Updated: 2021/05/23 17:03:30 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig			g_sig;

void			shell_init(t_datas *datas, t_cursor *cursor, char **envv)
{
	set_terminal(&cursor->cm, &cursor->dc, &cursor->ce);
	cursor->history = ft_new_deck();
	cursor->cur_history = cursor->history->tail;
	datas->env_list = array_to_list(envv, 0);
	datas->export_list = array_to_list(envv, 1);
	ft_rm_env(datas, "OLDPWD");
	ft_export_env(datas, NULL, "OLDPWD");
	datas->envv = envv;
	datas->fd.read = 0;
	datas->fd.write = 1;
	datas->ori_fd.err = dup(2);
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

void			make_blocks(char *buf, t_datas *datas)
{
	int			i;
	char		**blocks;

	blocks = ft_split(buf, ';');
	i = -1;
	while (blocks[++i])
	{
		if (g_sig.is_exit == 1)
		{
			printf("#\n");
			break ;
		}
		pipe_process(blocks[i], datas);
	}
	free_str_array(blocks);
}

int				main(int argc, char **argv, char **envv)
{
	char		buf[4096];
	t_datas		datas;
	t_cursor	cursor;
	int			i;

	shell_init(&datas, &cursor, envv);
	new_input_init(&cursor, buf, &i);
	while (argc && argv[0] && read(0, &cursor.c, sizeof(int)) > 0)
	{
		if (cursor.c != '\n')
		{
			read_char_process(buf, &cursor, &i);
			continue ;
		}
		back_terminal();
		ft_lstadd(cursor.history, ft_new_list(buf));
		cursor.cur_history = cursor.history->tail;
		if (buf[0] != '\n')
			write(1, "\n", 1);
		if (buf[0] != '\0' && buf[0] != '\n')
			if (syntax_error_check(datas.ori_fd.err, buf, &(datas.status)))
				make_blocks(buf, &datas);
		new_input_init(&cursor, buf, &i);
	}
	return (datas.status);
}
