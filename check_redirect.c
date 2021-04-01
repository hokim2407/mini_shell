#include "minishell.h"

char		*get_filename_from(char *str)
{
	char	*result;
	int		chr;
	int		i;
	int j;
	result = malloc(ft_strlen(str) + 1);
	i = -1;
	j = -1;
	while(str[++i] == ' ');
	while(str[i] && str[i] != ' '&& str[i] != '>' && str[i] != '<')
	{
        result[++j] = str[i++] ;
        str[i-1] = ' '; 
    }
	result[++j] = '\0';
	return result;
}

void check_redirect(char * pipe, t_fd *fd)
{
	int out_p;
	int in_p;
	int i;

	i = -1;
	while(pipe[++i])
	{
		if(pipe[i] == '>' && pipe[i + 1] && pipe[i + 1] == '>' )
		{
			i++;
			fd->write = open(get_filename_from(pipe + i + 1), O_WRONLY | O_APPEND | O_CREAT, 777);
			if(fd->write  == -1)
				fd->write  = 1;
		}
		else if(pipe[i] == '>')
		{
            pipe[i] = ' '; 
			fd->write = open(get_filename_from(pipe + i + 1), O_WRONLY | O_TRUNC | O_CREAT, 777);
	   char a[2];
	   a[0] = '0'+ fd->write;
	   a[1]='\0';
	   write(1,a,2);

			if(fd->write  == -1)
				fd->write  = 1;
		}
		else if(pipe[i] == '<')
		{
			fd->read = open(get_filename_from(pipe + i + 1), O_RDONLY);
			if(fd->read  == -1)
				fd->read  = 0;
		}
         // printf("[%s]\n",pipe);
	}

}
