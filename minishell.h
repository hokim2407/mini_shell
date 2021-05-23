/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hokim <hokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:49:36 by hokim             #+#    #+#             */
/*   Updated: 2021/05/23 20:42:00 by hokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <termcap.h>
# include <sys/types.h>
# include <sys/stat.h>

# define BACKSPACE 127
# define LEFT 4479771
# define RIGHT 4414235
# define UP 4283163
# define DOWN 4348699

# define HEADER "minishell> "
# define ERR_HEADER "bash: "

typedef struct		s_deck
{
	struct s_list	*head;
	struct s_list	*tail;
}					t_deck;

typedef struct		s_list
{
	struct s_list	*pre;
	void			*content;
	int				is_unseted;
	struct s_list	*next;
}					t_list;

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				key_len;
	int				val_len;
	struct s_list	*next;
}					t_env;

typedef struct		s_fd
{
	int				read;
	int				write;
	int				err;
}					t_fd;

typedef struct		s_datas
{
	t_deck			*env_list;
	t_deck			*export_list;
	t_fd			fd;
	t_fd			ori_fd;
	int				status;
	char			**envv;
}					t_datas;

typedef struct		s_cursor
{
	char			*cm;
	char			*dc;
	char			*ce;
	t_list			*cur_history;
	t_deck			*history;
	int				c;
	int				h;
	int				v;
	int				term_offset;
	int				max;
}					t_cursor;

typedef struct		s_sig
{
	int				sig;
	int				is_cat;
	int				is_exit;
}					t_sig;

int					mini_single_process(char *buf, t_datas *datas);
int					pipe_process(char *block, t_datas *datas);
int					exe_process(char **new_argv, t_datas *datas);
int					sh_process(char **new_argv, t_datas *datas);

int					ft_write_ch(int c);

void				set_terminal(char **cm, char **dc, char **ce);
void				set_again_terminal();
void				back_terminal();

void				check_cursor(t_cursor *cursor, char *buf, int *i);
void				get_cursor_position(int *h, int *v);
void				put_char_in_str(char *buf, char c, int nth);
void				push_new(t_cursor *cursor, char *buf);

t_deck				*ft_new_deck();
t_deck				*array_to_list(char **envv, int is_inorder);
t_list				*ft_new_list(void *value);
void				ft_lstadd(t_deck *deck, t_list *new_lst);
void				ft_lstdelone(t_list *one);
void				ft_lstadd_inorder(t_deck *deck, t_list *lst);

int					check_redirect(char *pipe, t_datas *datas);

char				**ft_split(char const *str, char c);
int					ft_strcmp(char *str1, char *str2);
int					ft_strlcmp(char *str1, char *str2, int len);
size_t				ft_strlen(const char *str);
int					is_valid_key(char *target);

t_list				*find_lst_by_key(t_deck *deck, char *data);
char				*find_value_by_key(t_deck *deck, char *key);

void				check_env_in_cmd(t_datas *datas, char **str);
void				rm_quato(char **buf);
int					get_quato(char *str, int util);
int					find_outquate_sign(char *str, int from);

void				ft_rm_env(t_datas *datas, char *target);
void				ft_export_env(t_datas *datas, char **argv, char *target);
void				ft_print_all_deck(t_datas datas);

size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				**ft_split_two(char *str, char c);
int					ft_strlcmp(char *str1, char *str2, int len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *str);
int					ft_strchr(const char *str, int value);
void				free_str_array(char **str);
char				*ft_itoa(int num);
int					ft_atoi(const char *str, char **new_argv);
int					ft_write(int fd, char *str);
char				*get_abs_path(char *original);
void				remove_char_in_str(char *buf, int nth);
char				**ft_one_str_arr(const char *str);

int					count_deck(t_deck *deck);

void				rm_chars_in_str(char *buf, int start, int len);
int					mini_single_process(char *buf, t_datas *datas);
void				read_char_process(char *buf, t_cursor *cursor, int *i);

void				sig_ft(int signum);
void				sig_ign();
void				sig_dfl();
void				sig_special(int signum);

int					check_file_state(t_fd fd, int is_check_write);

int					redirect_err(int fd, char *filename, int status);
int					print_export_err(int fd, int *status, char *cmd,
					char *err_cmd);
void				ft_print_all_export(t_datas datas);
int					print_env_err(int fd, char **argv);
int					print_err(int fd, char **argv, int status);
int					print_exit_err(t_datas *datas, char **new_argv);
int					print_status(int fd, int status);
int					is_n_option(char *argv);
int					syntax_error_check(int fd, char *buf, int *status);
void				new_input_init(t_cursor *cursor, char *buf, int *i);
void				pull_back_strs(char **strs, int i);

void				check_env_data_null_case(char **str,
					t_env env_data, int start, int *i);
char				**check_upper_case(char **new_argv);
char				**check_echo(char **new_argv);
void				change_pwd_env(t_datas *datas, char *old_path);
int					print_cd_err(int fd, char **argv, int status, int i);
char				**change_wave_to_home(char **new_argv, t_datas *datas);
#endif
