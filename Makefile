CC = gcc
CFLAGS = -lncurses #-Wall -Wextra -Werror
NAME = minishell
RM = rm -f
SRCS = check_redirect.c cursor.c env_cmd.c env_to_value.c exe_cmd.c ft_atoi.c \
ft_lst.c ft_split.c ft_strutils.c ft_strutils2.c get_abs_path.c main.c pipe.c sh_cmd.c
OBJS = $(SRCS:.c=.o)
.c.o :
	$(CC) $(CFLAGS) -c -o $@ $<
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
all : $(NAME)
clean:
	$(RM) $(OBJS) $(BOBJS)
fclean:	clean
	$(RM) $(NAME)
re : clean all
.PHONY:	all clean fclean re
