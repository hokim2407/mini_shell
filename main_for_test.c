/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:49:02 by hokim             #+#    #+#             */
/*   Updated: 2021/05/19 22:14:47 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig			g_sig;

void			shell_init(t_datas *datas, char **envv)
{
	datas->env_list = array_to_list(envv, 0);
	datas->export_list = array_to_list(envv, 1);
	datas->envv = envv;
	datas->fd.read = 0;
	datas->fd.write = 1;
	datas->status = 0;
}

void			new_init(char *buf, int *i)
{
	buf[0] = '\0';
	*i = 0;
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
		pipe_process(blocks[i], datas);
	free_str_array(blocks);
}

void			read_char(char *buf, char c, int *i)
{
	if (g_sig.sig == 'c')
	{
		g_sig.sig = 0;
		*i = 0;
		buf[0] = '\0';
		exit(0);
	}
	buf[(*i)++] = c;
	buf[*i] = '\0';
}

int				main(int argc, char **argv, char **envv)
{
	char		buf[4096];
	t_datas		datas;
	char		c;
	int			i;

	shell_init(&datas, envv);
	new_init(buf, &i);
	while (argc && argv[0] && read(0, &c, 1) > 0)
	{
		if (c != '\n')
		{
			read_char(buf, c, &i);
			continue;
		}
		if (buf[0] == '\0' || buf[0] == '\n')
		{
			new_init(buf, &i);
			continue;
		}
		if (buf[0] != '\0' && buf[0] != '\n')
			if (syntax_error_check(datas.ori_fd.err, buf, &(datas.status)))
				make_blocks(buf, &datas);
		new_init(buf, &i);
	}
	return (datas.status);
}
