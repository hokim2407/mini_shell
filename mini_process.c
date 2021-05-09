/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:48:52 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:51:20 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_sig_end;

void			mini_single_process2(char **new_argv, t_datas *datas)
{
	if (!ft_strcmp(new_argv[0], "cd") && new_argv[1] != NULL)
	{
		if (chdir(new_argv[1]) < 0)
			print_err(1);
	}
	else if (!ft_strcmp(new_argv[0], "env"))
		ft_print_all_deck(*datas->env_list);
	else if (!ft_strcmp(new_argv[0], "export"))
		ft_export_env(datas->env_list, datas->export_list, new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "unset"))
		ft_rm_env(datas->env_list, datas->export_list, new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "exit"))
		exit(0);
	else if (!ft_strcmp(new_argv[0], "$?"))
		printf("%d\n", datas->status / 256);
	else if (new_argv[0][0] == '/' ||
			!ft_strlcmp(new_argv[0], "./", 2) ||
			!ft_strlcmp(new_argv[0], "../", 3))
		sh_process(new_argv, datas);
	else
		exe_process(new_argv, datas);
}

int				mini_single_process(char *buf, t_datas *datas)
{
	char		**new_argv;
	int			i;

	i = -1;
	new_argv = ft_split(buf, ' ');
	check_env_in_cmd(new_argv, datas->env_list);
	rm_quato(new_argv);
	if (new_argv[0] == NULL)
		return (1);
	mini_single_process2(new_argv, datas);
	free_str_array(new_argv);
	return (0);
}

void			ascii_char_process(char *buf, t_cursor *cursor, int *i)
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
}

void			read_char_process(char *buf, t_cursor *cursor, int *i)
{
	if (g_sig_end == 'c')
	{
		g_sig_end = 0;
		cursor->max = 0;
		*i = 0;
		buf[0] = '\0';
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
