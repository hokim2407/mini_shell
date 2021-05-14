/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:49:16 by hokim             #+#    #+#             */
/*   Updated: 2021/05/09 19:49:18 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				get_cursor_position(int *h, int *v)
{
	int				i;
	char			buf[255];
	int				ret;
	int				temp;

	i = 0;
	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i] && (buf[i] < '0' || buf[i] > '9') && buf[i + 1] != ';')
		++i;
	*v = atoi(buf + i) - 1;
	while (buf[i] && buf[i] != ';')
		++i;
	*h = atoi(buf + i + 1) - 1;
}

void				set_terminal(char **cm, char **dc, char **ce)
{
	struct termios	terminal;
	char			*env;

	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~ICANON;
	terminal.c_lflag &= ~ECHO;
	terminal.c_cc[VMIN] = 1;
	terminal.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	env = getenv("TERM");
	if (env == NULL)
		env = "xterm";
	tgetent(NULL, env);
	*cm = tgetstr("cm", NULL);
	*dc = tgetstr("dc", NULL);
	*ce = tgetstr("ce", NULL);
}

void				set_again_terminal(void)
{
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~ICANON;
	terminal.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

void				back_terminal(void)
{
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag |= ICANON;
	terminal.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}
