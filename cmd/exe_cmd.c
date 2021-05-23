/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:43:51 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/23 20:20:30 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern				t_sig g_sig;

int					in_dir(char *path, char *cmd)
{
	DIR				*dir_ptr;
	struct dirent	*file;

	dir_ptr = NULL;
	file = NULL;
	if ((dir_ptr = opendir(path)) == NULL)
		return (0);
	while ((file = readdir(dir_ptr)))
	{
		if (!ft_strcmp(file->d_name, cmd))
			return (1);
	}
	closedir(dir_ptr);
	return (0);
}

char				*get_executable(char *path, char *cmd)
{
	char			**paths;
	int				i;
	char			*temp;

	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	temp = NULL;
	i = -1;
	while (paths[++i])
	{
		if (in_dir(paths[i], cmd))
			break ;
	}
	if (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(temp);
		temp = ft_strjoin(paths[i], cmd);
	}
	free_str_array(paths);
	if (temp == NULL)
		temp = cmd;
	return (temp);
}

void				exe_cmd(char **new_argv, t_datas *datas)
{
	char			*temp;
	int				offset;
	t_list			*temp_list;

	offset = 0;
	sig_dfl();
	new_argv = check_upper_case(new_argv);
	temp_list = find_lst_by_key(datas->env_list, "PATH");
	if (!(temp = get_executable(find_value_by_key(datas->env_list, "PATH"),
		new_argv[0])) || temp_list->is_unseted || temp[0] != '/')
	{
		if (!(ft_strcmp(new_argv[0], "echo")))
		{
			ft_write(datas->ori_fd.write, new_argv[1]);
			exit(ft_write(datas->ori_fd.write, "\n") & 0);
		}
		exit(print_err(datas->ori_fd.err, new_argv, 127));
	}
	dup2(datas->fd.read, 0);
	dup2(datas->fd.write, 1);
	dup2(datas->ori_fd.err, 2);
	if (!ft_strcmp(new_argv[0], "echo"))
		new_argv = check_echo(new_argv);
	if (execve(temp, new_argv, datas->envv) == -1)
		exit(print_err(datas->ori_fd.err, new_argv, 127));
}

int					exe_process(char **new_argv, t_datas *datas)
{
	int				pid;

	pid = fork();
	if (pid == 0)
		exe_cmd(new_argv, datas);
	else
	{
		g_sig.is_cat = !ft_strcmp(new_argv[0], "cat");
		signal(SIGINT, sig_special);
		signal(SIGQUIT, sig_special);
		waitpid(pid, &datas->status, 0);
	}
	return (1);
}
