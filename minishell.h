#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include  <signal.h>
#include <dirent.h> 

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

void 	ft_env(t_list *values);
void 	ft_rm_env(t_deck * deck, char *target);
void 	ft_add_env(t_deck * deck, char *target);

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
void	free_str_array(char **str);

void	check_env_in_cmd(char **str,t_deck *env);
void	check_redirect(char * pipe, t_fd *fd);
char	*get_abs_path(char *original);

int		pipe_process (int argc, char **argv);
int exe_process(char **new_argv, char **envv, t_deck *env_list);
int sh_process(char **new_argv, char **envv, t_deck *deck);

int ft_write(char *str);
#endif
