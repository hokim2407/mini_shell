/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:48:52 by hokim             #+#    #+#             */
/*   Updated: 2021/05/23 20:32:09 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_sig			g_sig;

int				mini_env_process(char **new_argv, t_datas *datas)
{
	int			i;

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
	{
		if (new_argv[1])
			ft_rm_env(datas, new_argv[1]);
	}
	else
		return (0);
	return (1);
}

void			cd_process(char **new_argv, t_datas *datas, int i)
{
	int			result;
	char		*old_path;
	char		*temp;

	old_path = find_value_by_key(datas->env_list, "PWD");
	if (new_argv[i] == NULL || !ft_strcmp(new_argv[i], "~"))
	{
		temp = find_value_by_key(datas->env_list, "HOME");
		result = chdir(temp);
		free(temp);
	}
	else if (new_argv[i][0] != '\0')
		result = chdir(new_argv[i]);
	if (result < 0)
	{
		datas->status = print_cd_err(datas->ori_fd.err, new_argv, 0, i);
		free(old_path);
		return ;
	}
	change_pwd_env(datas, old_path);
}

void			mini_single_process2(char **new_argv, t_datas *datas)
{
	int			i;

	i = 0;
	if (mini_env_process(new_argv, datas))
		return ;
	if (!ft_strcmp(new_argv[0], "cd"))
	{
		if (new_argv[1] == NULL)
			cd_process(new_argv, datas, 1);
		while (new_argv[++i])
			cd_process(new_argv, datas, i);
	}
	else if (!ft_strcmp(new_argv[0], "."))
	{
		ft_write(datas->ori_fd.err, ERR_HEADER);
		ft_write(datas->ori_fd.err, ".: filename argument required\n");
		ft_write(datas->ori_fd.err, ".:usage: . filename [arguments]\n");
		datas->status = 2 * 256;
		return ;
	}
	else if (new_argv[0][0] == '/' || !ft_strlcmp(new_argv[0], "./", 2) ||
			!ft_strlcmp(new_argv[0], "../", 3))
		sh_process(new_argv, datas);
	else
		exe_process(new_argv, datas);
}

int				print_exit_err(t_datas *datas, char **new_argv)
{
	int			i;
	long long	num;

	i = 0;
	num = -1;
	while (new_argv[1] && new_argv[1][++num])
		if ((new_argv[1][num] < '0') || (new_argv[1][num] > '9'))
			i++;
	if (new_argv[1] != NULL && new_argv[2] &&
		(i == 0 || ((new_argv[1][0] == '+') || (new_argv[1][0] == '-'))))
		return (datas->status = print_err(datas->ori_fd.err, new_argv, 1));
	if (new_argv[1] != NULL)
	{
		num = 0;
		num = ft_atoi(new_argv[1], new_argv);
		if (num != 0 && i <= 1)
			exit(num);
		else if (num == 0 && i <= 1 && (((new_argv[1][0] >= '0')
			&& (new_argv[1][0] <= '9'))
			|| ((new_argv[1][0] == '+') || (new_argv[1][0] == '-'))))
			exit(0);
		exit(print_err(datas->ori_fd.err, new_argv, 255));
	}
	return (0);
}

int				mini_single_process(char *buf, t_datas *datas)
{
	char		**new_argv;

	new_argv = ft_split(buf, ' ');
	new_argv = change_wave_to_home(new_argv, datas);
	rm_quato(new_argv);
	if (new_argv[0] && new_argv[0][0] == '\0')
		new_argv++;
	if (new_argv[0] == NULL)
		return (1);
	if (!ft_strcmp(new_argv[0], "exit"))
	{
		write(datas->ori_fd.err, "exit\n", 5);
		if (print_exit_err(datas, new_argv))
		{
			g_sig.is_exit = 1;
			return (datas->status = 256);
		}
		exit(datas->status);
	}
	mini_single_process2(new_argv, datas);
	free_str_array(new_argv);
	return (0);
}
