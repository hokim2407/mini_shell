/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:30:35 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/23 20:31:20 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_sig			g_sig;

int				err_msg(int fd, char **argv, int status)
{
	if (status == 127)
		ft_write(fd, "command not found\n");
	else if (status == 1)
		ft_write(fd, "too many arguments\n");
	else if (status == 126)
		ft_write(fd, "is a directory\n");
	else if (status == 255)
	{
		ft_write(fd, argv[1]);
		ft_write(fd, ": numeric argument required\n");
	}
	else
		return (1);
	return (0);
}

int				print_cd_err(int fd, char **argv, int status, int i)
{
	int			len;

	len = -1;
	while (argv[++len])
		;
	ft_write(fd, ERR_HEADER);
	ft_write(fd, argv[0]);
	ft_write(fd, ": ");
	if (err_msg(fd, argv, status))
	{
		ft_write(fd, argv[i]);
		ft_write(fd, ": ");
		ft_write(fd, strerror(errno));
		ft_write(fd, "\n");
		status = 256;
	}
	return (status);
}

int				print_err(int fd, char **argv, int status)
{
	int			len;

	len = -1;
	while (argv[++len])
		;
	ft_write(fd, ERR_HEADER);
	ft_write(fd, argv[0]);
	ft_write(fd, ": ");
	if (err_msg(fd, argv, status))
	{
		ft_write(fd, argv[len - 1]);
		ft_write(fd, ": ");
		ft_write(fd, strerror(errno));
		ft_write(fd, "\n");
		status = 256;
	}
	return (status);
}

int				print_env_err(int fd, char **argv)
{
	int			len;

	len = -1;
	while (argv[++len])
		;
	ft_write(fd, argv[0]);
	ft_write(fd, ": ");
	ft_write(fd, argv[len - 1]);
	ft_write(fd, ": ");
	ft_write(fd, "No such file or directory");
	ft_write(fd, "\n");
	return (1);
}

int				print_export_err(int fd, int *status, char *cmd, char *err_cmd)
{
	int			len;

	len = -1;
	ft_write(fd, ERR_HEADER);
	ft_write(fd, cmd);
	ft_write(fd, ": `");
	ft_write(fd, err_cmd);
	ft_write(fd, "\': ");
	ft_write(fd, "not a valid identifier");
	ft_write(fd, "\n");
	*status = 256;
	return (1);
}
