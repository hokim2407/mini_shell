/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:48:52 by hokim             #+#    #+#             */
/*   Updated: 2021/05/21 16:30:29 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			mini_env_process(char **new_argv, t_datas *datas)
{
	int		i;

	i = 0;
	if (!ft_strcmp(new_argv[0], "env"))
	{
		if (new_argv[1] == NULL)
			ft_print_all_deck(*datas);
		else
			datas->status = print_env_err(datas->ori_fd.err, new_argv);
	}
	else if (!ft_strcmp(new_argv[0], "export"))
	{
		if (new_argv[1] == NULL)
			ft_print_all_export(*datas);
		while (new_argv[++i])
			ft_export_env(datas, new_argv, new_argv[i]);
	}
	else if (!ft_strcmp(new_argv[0], "unset"))
		ft_rm_env(datas, new_argv[1]);
	else
		return (0);
	return (1);
}

void		home_cd(t_datas *datas)
{
	char	*home;

	home = ft_strdup(find_value_by_key(datas->env_list, "HOME"));
	chdir(home);
}

void		mini_single_process2(char **new_argv, t_datas *datas)
{
	if (mini_env_process(new_argv, datas))
		return ;
	if (!ft_strcmp(new_argv[0], "cd"))
	{
		if (new_argv[1] == NULL)
		{
			home_cd(datas);
			return ;
		}
		else if (new_argv[1] != NULL)
		{
			if (chdir(new_argv[1]) < 0)
				datas->status = print_err(datas->ori_fd.err, new_argv, 0);
		}
	}
	else if (!ft_strcmp(new_argv[0], "."))
	{
		ft_write(2, "minishell: .: filename argument required\n");
		ft_write(2, ".:usage: . filename [arguments]\n");
		return ;
	}
	else if (new_argv[0][0] == '/' ||
			!ft_strlcmp(new_argv[0], "./", 2) ||
			!ft_strlcmp(new_argv[0], "../", 3))
		sh_process(new_argv, datas);
	else
		exe_process(new_argv, datas);
}

int			mini_single_process(char *buf, t_datas *datas)
{
	char	**new_argv;

	new_argv = ft_split(buf, ' ');
	check_env_in_cmd(new_argv, datas->env_list, datas->status);
	rm_quato(new_argv);
	if (new_argv[0] && new_argv[0][0] == '\0')
		new_argv++;
	if (new_argv[0] == NULL)
		return (1);
	if (!ft_strcmp(new_argv[0], "exit"))
	{
		write(2, "exit\n", 5);
		if (print_exit_err(datas, new_argv))
			return (datas->status = 256);
		exit(datas->status);
	}
	mini_single_process2(new_argv, datas);
	free_str_array(new_argv);
	return (0);
}
