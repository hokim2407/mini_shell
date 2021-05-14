
#include "../minishell.h"

int				print_err(int fd, char **argv, int status)
{
	int			len;

	len = -1;
	while (argv[++len])
		;
	ft_write(fd, "minishell: ");
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

int			print_export_err(int fd, char **argv)
{
	int		len;

	len = -1;
	while (argv[++len])
		;
	ft_write(fd, "minishell: ");
	ft_write(fd, argv[0]);
	ft_write(fd, ": `");
	ft_write(fd, argv[len - 1]);
	ft_write(fd, "\': ");
	ft_write(fd, "not a valid identifier");
	ft_write(fd, "\n");
	return (1);
}

int				print_status(int fd, int status)
{
	char		*str;

	str = ft_itoa(status / 256);
	write(fd, "minishell: ", 11);
	write(fd, str, ft_strlen(str));
	write(fd, ": command not found\n", 20);
	return (status);
}
