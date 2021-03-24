char *check_sigle(char *s, char c)
{
    int i;
	int j;
    char *new;

    i = 0;
	j = 0;
    new
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
