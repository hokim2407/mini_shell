#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <dirent.h> 
#include <termios.h>
#include <termcap.h>

#define BACKSPACE 127
#define LEFT 4479771
#define RIGHT 4414235
#define UP 4283163
#define DOWN 4348699

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
	char			*dc;
	char			*ce;
	t_list			*cur_history;
	t_deck			*history;
	int				c;
	int				h;
	int				v;

	int				term_offset;
	// int				i;
	int				max;
}					t_cursor;

int 	mini_single_process(char *buf, t_datas *datas);
int		pipe_process (char *block, t_datas *datas);
int		exe_process(char **new_argv, t_datas *datas);
int		sh_process(char **new_argv, t_datas *datas);

int			ft_write_ch(int c);

void set_terminal(char **cm, char **dc, char **ce);
void set_again_terminal();
void back_terminal();

void check_cursor(t_cursor *cursor, char * buf, int *i);
void get_cursor_position(int *h, int *v);
void put_char_in_str(char *buf, char c, int nth);
void push_new(t_cursor *cursor, char *buf);

t_deck	*ft_new_deck();
t_deck	*array_to_list(char **envv, int is_inorder);
t_list	*ft_new_list(void* value);
void	ft_lstadd(t_deck * deck, t_list *new_lst);
void	ft_lstdelone(t_list *one);
void	ft_lstadd_inorder(t_deck * deck, t_list *lst);

void	check_redirect(char * pipe, t_fd *fd);

char	**ft_split(char const *str, char c);
int		ft_strcmp(char *str1, char *str2);
int		ft_strlcmp(char *str1, char *str2, int len);
size_t	ft_strlen(const char *str);
int		is_valid_key(char *target);

t_list	*find_lst_by_key(t_deck * deck, char *data);
char	*find_value_by_key(t_deck * deck, char *key);

void	check_env_in_cmd(char **str,t_deck *env);
void 	rm_quato(char **buf);
int get_quato(char *str, int util);


void	ft_rm_env(t_deck * env,t_deck * export, char *target);
void	ft_export_env(t_deck * env,t_deck * export, char *target);
void 	ft_print_all_deck(t_deck deck);


size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**ft_split_two(char *str, char c);
int			ft_strlcmp(char *str1, char *str2, int len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *str);
int		ft_strchr(const char *str, int value);
void	free_str_array(char **str);


char	*get_abs_path(char *original);



int ft_write(char *str);

void remove_char_in_str(char *buf,int nth);

int		count_deck(t_deck * deck);

void print_err(int fd);

char		**ft_one_str_arr(const char *str);

void		rm_chars_in_str(char *buf, int start, int len);

#endif
