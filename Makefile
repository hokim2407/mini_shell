CC = gcc
CFLAGS = -Wall -Wextra -Werror#-g3 -fsanitize=address#
NAME = minishell
RM = rm -f

CMD_SRCS = check_redirect.c env_cmd.c exe_cmd.c ft_pipe.c mini_process.c sh_cmd.c 
ETC_SRCS = error.c signal.c 
LIST_SRCS = ft_lst_add.c ft_lst_find.c ft_lst_new.c 
STRUTILS_SRCS = env_to_value.c ft_quato.c ft_split.c ft_strsplit_two.c ft_strutils_basic.c \
				ft_strutils_etc.c ft_strutils_make.c get_abs_path.c 
TERMINAL_SRCS = cursor.c term.c 

SRCS = main.c $(addprefix ./cmd/, ${CMD_SRCS}) $(addprefix ./etc/, ${ETC_SRCS}) \
		$(addprefix ./list/, ${LIST_SRCS}) $(addprefix ./strutils/, ${STRUTILS_SRCS}) \
		$(addprefix ./terminal/, ${TERMINAL_SRCS}) 
		
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


norm : 
	norminette *.c *.h cmd/*.c etc/*.c list/*.c strutils/*.c terminal/*.c

add :
	git add *.c *.h cmd etc list strutils terminal Makefile

.PHONY:	all clean fclean re
