
#include "minishell.h"
#include <string.h>
#include <errno.h>

pid_t pid;
char *head;
int read_fd;
int write_fd;
void sig_ft()
{
	if (SIGINT != 2)
		signal(SIGINT, SIG_DFL);
	else
	{
		write(1, "\n", 1);
		write(1, head, ft_strlen(head));
	}
}

int mini_pipe_process(char *buf, t_datas datas)
{
	char **new_argv;
	int i;

	i = -1;
	new_argv = ft_split(buf, ' ');

	while (new_argv[++i])
		check_env_in_cmd(new_argv + i, datas.env_list);
	if (new_argv[0] == NULL)
		return 1;
	if (!ft_strcmp(new_argv[0], "cd") && new_argv[1] != NULL)
		;
	else if (!ft_strcmp(new_argv[0], "env"))
		;
	else if (!ft_strcmp(new_argv[0], "export"))
		;
	else if (!ft_strcmp(new_argv[0], "unset"))
		;
	else if (!ft_strcmp(new_argv[0], "exit"))
		exit(0);
	else if (new_argv[0][0] == '/' || !ft_strlcmp(new_argv[0], "./", 2) || !ft_strlcmp(new_argv[0], "../", 3))
		sh_process(new_argv, datas);
	else
		exe_process(new_argv, datas);
	return 1;
}

int mini_single_process(char *buf, t_datas datas)
{
	char **new_argv;
	int i;

	i = -1;
	new_argv = ft_split(buf, ' ');

	while (new_argv[++i])
		check_env_in_cmd(new_argv + i, datas.env_list);
	if (new_argv[0] == NULL)
		return 1;
	if (!ft_strcmp(new_argv[0], "cd") && new_argv[1] != NULL)
		chdir(new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "env"))
		ft_print_all_deck(*datas.env_list);
	else if (!ft_strcmp(new_argv[0], "export"))
		ft_add_env(datas.env_list, new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "unset"))
		ft_rm_env(datas.env_list, new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "exit"))
		exit(0);
	else if (new_argv[0][0] == '/' || !ft_strlcmp(new_argv[0], "./", 2) || !ft_strlcmp(new_argv[0], "../", 3))
		sh_process(new_argv, datas);
	else
		exe_process(new_argv, datas);
	return 1;
}

void set_terminal(char **cm, char **dc, char **ce)
{
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~ICANON;
	terminal.c_lflag &= ~ECHO;
	terminal.c_cc[VMIN] = 1;
	terminal.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);

	char *env = getenv("TERM");
	if (env == NULL)
		env = "xterm";

	tgetent(NULL, env);		   // xterm 설정 사용
	*cm = tgetstr("cm", NULL); //cursor motion

	*dc = tgetstr("dc", NULL); //clear line from cursor

	*ce = tgetstr("ce", NULL); //clear line from cursor
}

int main2(int argc, char **argv, char **envv)
{
	char *cm;
	char *ec;

	char *ce;
	set_terminal(&cm, &ec, &ce);
	int c = 0;
	while (read(0, &c, sizeof(int)) > 0 && c != '\n')
	{
		printf("%d\n", c);
	}

	return 1;
}

int main(int argc, char **argv, char **envv)
{
	char buf[4096];
	t_datas datas;
	char **new_argv;
	int i;
	char **blocks;
	int c;
	char *cm;
	char *ec;
	t_list *cur_history;
	char *ce;
	int max;
	t_deck *history = ft_new_deck();
	set_terminal(&cm, &ec, &ce);
	head = "mini_shell> ";
	datas.env_list = array_to_list(envv);
	datas.envv = envv;

	while (1)
	{
		max = 0;
		datas.fd.read = 0;
		datas.fd.write = 1;
		write(1, head, ft_strlen(head));
		int i = 0;
		c = 0;
		while (read(0, &c, sizeof(int)) > 0 && c != '\n')
		{
			int h;
			int v;
			//			get_cursor_position(&col, &row);

			get_cursor_position(&h, &v);
			if (c == LEFT)
			{
				move_cursor_left(&h, &v, cm, &i);
				//	write(1, "LEFT",4);
			}
			else if (c == RIGHT)
			{
				move_cursor_right(&h, &v, cm, &i, max);
				//	write(1, "RIGHT",5);
			}
			if (c == UP)
			{
				if (cur_history->pre != history->head)
				{
					cur_history = cur_history->pre;
					h = ft_strlen(cur_history->content) ;
					i = h;
					max = h;
					ft_strlcpy(buf, cur_history->content, h + 1);
					h += HEADER_OFFSET - 2;
					push_new(&h, &v, cm, ce, buf);
				}
				//	write(1, "LEFT",4);
			}
			else if (c == DOWN)
			{

				if (cur_history->next != history->tail)
				{
					cur_history = cur_history->next;
					h = ft_strlen(cur_history->content) ;

					i = h;
					max = h;
					ft_strlcpy(buf, cur_history->content, h + 1);

					h += HEADER_OFFSET - 2;
					push_new(&h, &v, cm, ce, buf);
				}
				//	write(1, "RIGHT",5);
			}
			else if (c == BACKSPACE)
			{

				if (i == max)
				{
					buf[i - 1] = '\0';
				}
				else if (i >= 0)
					remove_char_in_str(buf, i - 1);
				delete_end(&h, &v, cm, ec, &i, &max);

				//write(1, "BACKSPACE",9);
			}
			else if (c < 127)
			{
				i++;
				if (max < i)
				{
					buf[i - 1] = c;

					write(1, buf + i - 1, 1);
					max++;
				}
				else
				{
					put_char_in_str(buf, c, i - 1);
					push_new(&h, &v, cm, ce, buf);
					max++;
				}
			}
			c = 0;
			buf[max + 1] = '\0';
		}

		ft_lstadd(history, ft_new_list(NULL, ft_strdup(buf), NULL));
		cur_history = history->tail;
		if (buf[i] != '\n')
			write(1, "\n", 1);
		if (buf[0] == '\0' || buf[0] == '\n')
			continue;
		blocks = ft_split(buf, ';');
		i = -1;

		while (blocks[++i])
		{
			pipe_process(blocks[i], datas);
		}
	}
}
