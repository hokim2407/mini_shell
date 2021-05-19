/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:49:02 by hokim             #+#    #+#             */
/*   Updated: 2021/05/19 20:40:46 by hyerkim          ###   ########.fr       */
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

void			new_input_init(char *buf, int *i)
{
	buf[0] = '\0';
	*i = 0;
	signal(SIGINT, sig_ft);
	signal(SIGQUIT, sig_ft);
}

int				main(int argc, char **argv, char **envv)
{
	char		buf[4096];
	t_datas		datas;
	char		c;
	int			i;
	char		**blocks;

	shell_init(&datas, envv);
	new_input_init(buf, &i);
	while (argc && argv[0] && read(0, &c, 1) > 0)
	{
		if (c != '\n')
		{
			if (g_sig.sig == 'c')
			{
				g_sig.sig = 0;
				i = 0;
				buf[0] = '\0';
				exit(0);
			}
			buf[i++] = c;
			buf[i] = '\0';
			continue;
		}
		if (buf[0] == '\0' || buf[0] == '\n')
		{
			new_input_init(buf, &i);
			continue;
		}
		blocks = ft_split(buf, ';');
		i = -1;
		while (blocks[++i])
			pipe_process(blocks[i], &datas);
		free_str_array(blocks);
		new_input_init(buf, &i);
	}
}
