/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:30:35 by hyerkim           #+#    #+#             */
/*   Updated: 2021/05/18 13:30:37 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			print_err(int fd, char **argv, int status)
{
	int		len;

	len = -1;
	fd = 2;
	while (argv[++len])
		;
	ft_write(1, "minishell: ");
	ft_write(fd, argv[0]);
	ft_write(fd, ": ");
	if (status == 127)
		ft_write(fd, "command not found\n");
	else if (status == 255)
	{
		ft_write(fd, argv[1]);
		ft_write(fd, ": numeric argument required\n");
	}
	else
	{
		ft_write(fd, argv[len - 1]);
		ft_write(fd, ": ");
		ft_write(fd, strerror(errno));
		ft_write(fd, "\n");
	}
	return (status);
}

int			print_env_err(int fd, char **argv)
{
	int		len;

	len = -1;
	fd = 2;
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

int			print_export_err(int fd, char *cmd, char *err_cmd)
{
	int		len;

	len = -1;
	fd = 2;
	ft_write(fd, "minishell: ");
	ft_write(fd, cmd);
	ft_write(fd, ": `");
	ft_write(fd, err_cmd);
	ft_write(fd, "\': ");
	ft_write(fd, "not a valid identifier");
	ft_write(fd, "\n");
	return (1);
}

int			print_status(int fd, int status)
{
	char	*str;

	fd = 2;
	str = ft_itoa(status / 256);
	write(fd, "minishell: ", 11);
	write(fd, str, ft_strlen(str));
	write(fd, ": command not found\n", 20);
	return (status);
}
