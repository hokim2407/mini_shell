char *check_sigle(char *s, char c)
{
    int i;
	  int j;
    char *new;


    i = 0;
<<<<<<< HEAD
	j = 0;
    new = malloc(ft_strlen(s) + 1);
=======
	  j = 0;
    new = malloc(ft_strlen(s));
>>>>>>> a4f8bed6a309539885bb154f305cac7882b489e8
    while (s[i])
    {
        if (s[i] != c)
		{
			new[j] = s[i];
			j++;
		}
		i++;
    }
  
	new[j] = '\0';
	return (new);

}
