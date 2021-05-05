CC = gcc
CFLAGS = #-Wall -Wextra -Werror
NAME = minishell
RM = rm -f
SRCS = env_cmd.c ft_lst_add.c ft_pipe.c ft_strutils_basic.c get_abs_path.c check_redirect.c env_to_value.c \
		ft_lst_find.c ft_quato.c ft_strutils_etc.c main.c sh_cmd.c cursor.c exe_cmd.c ft_lst_new.c ft_split.c \
		ft_strutils_make.c
OBJS = $(SRCS:.c=.o)
.c.o :
	$(CC) $(CFLAGS) -c -o $@ $<
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -lncurses -o $@ $^
all : $(NAME)
clean:
	$(RM) $(OBJS) $(BOBJS)
fclean:	clean
	$(RM) $(NAME)
re : clean all
.PHONY:	all clean fclean re
