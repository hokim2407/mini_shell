
#include "minishell.h"
#include <string.h>
#include <errno.h>

int sig_end;
void sig_ft(int signum)
{
	if (SIGINT == signum)
	{
		write(1,"\n",1);
		write(1,HEADER,HEADER_OFFSET);
		sig_end = 'c';
	}	
	else if (SIGQUIT == signum)
		;
}

int mini_pipe_process(char *buf, t_datas *datas)
{
	char **new_argv;
	int i;

	i = -1;
	new_argv = ft_split(buf, ' ');
	while (new_argv[++i])
		check_env_in_cmd(new_argv + i, datas->env_list);
		rm_quato(new_argv);
	if (new_argv[0] == NULL)
		return 1;

	else if (new_argv[0][0] == '/' || !ft_strlcmp(new_argv[0], "./", 2) || !ft_strlcmp(new_argv[0], "../", 3))
		sh_process(new_argv, datas);
	else
		exe_process(new_argv, datas);
	return 1;
}

int mini_single_process(char *buf, t_datas *datas)
{
	char **new_argv;
	int i;

	i = -1;
	new_argv = ft_split(buf, ' ');
	while (new_argv[++i])
		check_env_in_cmd(new_argv + i, datas->env_list);
		rm_quato(new_argv);
	if (new_argv[0] == NULL)
		return 1;
	if (!ft_strcmp(new_argv[0], "cd") && new_argv[1] != NULL)
		chdir(new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "env"))
		ft_print_all_deck(*datas->env_list);
	else if (!ft_strcmp(new_argv[0], "export"))
		ft_export_env(datas->env_list,datas->export_list, new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "unset"))
		ft_rm_env(datas->env_list, new_argv[1]);
	else if (!ft_strcmp(new_argv[0], "exit"))
		exit(0);
	else if (!ft_strcmp(new_argv[0], "$?"))
		printf("%d\n",datas->status/256);
	else if (new_argv[0][0] == '/' || !ft_strlcmp(new_argv[0], "./", 2) || !ft_strlcmp(new_argv[0], "../", 3))
		sh_process(new_argv, datas);
	else
		exe_process(new_argv, datas);
	return 0;
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


int main(int argc, char **argv, char **envv)
{
	char buf[4096];
	t_datas datas;
	t_cursor cursor;
	int i;
	char **blocks;

	sig_end = 0;

	set_terminal(&cursor.cm, &cursor.dc, &cursor.ce);

	cursor.history = ft_new_deck();
	datas.env_list = array_to_list(envv,0);
	datas.export_list = array_to_list(envv,1);
	datas.envv = envv;
	datas.fd.read = 0;
	datas.fd.write = 1;
	datas.status = 0;
	signal(SIGINT,sig_ft);
	signal(SIGQUIT,sig_ft);
	while (1)
	{
		write(1, HEADER, ft_strlen(HEADER));
		cursor.max = 0;
		i = 0;
		cursor.c = 0;
		while (read(0, &cursor.c, sizeof(int)) > 0 && cursor.c != '\n')
		{
			if(sig_end == 'c' )
			{
				sig_end = 0;
				cursor.max = 0;
				i = 0;
				buf[0] = '\0';
			}
			if((cursor.c == 4 && cursor.max != 0)|| cursor.c == '\t')
				{
					continue;
				}
			if(cursor.c == 4)
			{
				write(1,"exit\n",5);
				exit(0);
			}
			check_cursor(&cursor, buf, &i);
			if (cursor.c < 127)
			{
				if (cursor.max < ++i)
				{
					buf[i - 1] = cursor.c;
					write(1, buf + i - 1, 1);
				}
				else
				{
					put_char_in_str(buf, cursor.c, i - 1);
					push_new(&cursor.h, &cursor.v, cursor.cm, cursor.ce, buf);
				}
				cursor.max++;
			}
			cursor.c = 0;
			buf[cursor.max + 1] = '\0';
		}
		buf[cursor.max + 1] = '\0';
		ft_lstadd(cursor.history, ft_new_list(ft_strdup(buf)));
		cursor.cur_history = cursor.history->tail;
		if (buf[i] != '\n')
			write(1, "\n", 1);
		if (buf[0] == '\0' || buf[0] == '\n')
			continue;
	
		blocks = ft_split(buf, ';');
		i = -1;
		while (blocks[++i])
			pipe_process(blocks[i], &datas);
	}
}
