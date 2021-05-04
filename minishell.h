#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include  <signal.h>
#include <dirent.h> 
#include <termios.h>
#include <termcap.h>

#define BACKSPACE 127
#define LEFT 4479771
#define RIGHT 4414235

#define UP 4283163
#define DOWN 4348699

#define HEADER_OFFSET 13


#define HEADER "mini_shell> "

typedef struct		s_deck
{
	struct s_list	*head;
	struct s_list	*tail;
}					t_deck;

typedef struct		s_list
{
	struct s_list	*pre;
	void			*content;
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
	char			*ec;
	char			*ce;
	t_list			*cur_history;
	t_deck			*history;
	int				c;
	int				h;
	int				v;
	// int				i;
	int				max;
}					t_cursor;

void 	ft_env(t_list *values);
void 	ft_rm_env(t_deck * deck, char *target);
void ft_export_env(t_deck * env,t_deck * export, char *target);

t_deck	*ft_new_deck();
t_list	*ft_new_list(t_list * pre, void* value, t_list * next);
t_deck	*array_to_list(char **envv);
void	ft_lstdelone(t_list *one);
void	ft_lstadd(t_deck * deck, t_list *new_lst);
t_list	*ft_lstfind(t_deck * deck, char *data);
char	*find_value_in_list(t_deck * deck, char *key);
void 	ft_print_all_deck(t_deck deck);
void 	ft_r_print_all_deck(t_deck deck);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**ft_split(char const *str, char c);
char	**ft_split_two(char *str, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int 	ft_strtrim_quato(char **str);
char	*ft_strdup(const char *str);
int		ft_strcmp(char *str1, char *str2);
int		ft_strlcmp(char *str1, char *str2, int len);
int		ft_strchr(const char *str, int value);
int			ft_atoi(const char *str);
void	free_str_array(char **str);

void	check_env_in_cmd(char **str,t_deck *env);
void	check_redirect(char * pipe, t_fd *fd);
char	*get_abs_path(char *original);

int 	mini_single_process(char *buf, t_datas *datas);
int		mini_pipe_process(char *buf, t_datas *datas);
int		pipe_process (char *block, t_datas *datas);
int		exe_process(char **new_argv, t_datas *datas);
int		sh_process(char **new_argv, t_datas *datas);

int ft_write(char *str);
int			ft_write_ch(int c);

void get_cursor_position(int *col, int *row);
void	move_cursor_left(int *col, int *row, char *cm, int * i);
void	move_cursor_right(int *h, int *v, char *cm, int * i, int max);
void	delete_end(int *h, int *v, char *cm, char *ec, int * i, int * max);
void remove_char_in_str(char *buf,int nth);
void put_char_in_str(char *buf, char c, int nth);
void push_new(int *h, int *v, char *cm, char *ce, char * buf);

void check_cursor(t_cursor *cursor, char * buf, int *i);
int		count_deck(t_deck * deck);
void		ft_lst_import(t_list *front_lst, t_list *new_lst, t_list *next_lst);
t_deck *  ft_make_export_list(char **target);
#endif
