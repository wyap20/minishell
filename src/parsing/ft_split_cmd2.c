#include "../../minishell.h"

/*part of ft_split_cmd*/

/* 
  find the second quote of quote pair;
  find the quote that closes the pair
*/
int	ft_get_b(int *id, int a, int q)
{
	int	flag;

	flag = 0;
	while (id[a] != -1)
	{
		if (id[a] == q)
			flag++;
		if (flag == 2)
			break ;
		a++;
	}
	return (a);
}

/*
fills in character between quotes with index identifier or quotes
either 4 (double quotes) or 2 (single quote)

a: first quote of quote pair
b: second quote of quote pair 
*/
int	ft_fill_in(int *id, int i, int q)
{
	int	a;
	int	b;

	a = i;
	b = ft_get_b(id, a, q);
	while (a != b)
	{
		id[a] = q;
		a++;
	}
	return (a);
}

int	group_count(int *d, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (d[i] != -1)
	{
		while (d[i] == c && d[i] != -1)
			i++;
		if (d[i] != -1)
			count++;
		while (d[i] != c && d[i] != -1)
			i++;
	}
	return (count);
}

char	*group_dup(int *d, const char *s, int c)
{
	int		len;
	int		i;
	char	*group;

	i = 0;
	len = 0;
	while (d[len] != -1 && d[len] != c)
		len++;
	group = (char *) malloc(sizeof(char) * (len + 1));
	if (group == NULL)
		return (NULL);
	while (i < len)
	{
		group[i] = s[i];
		i++;
	}
	group[i] = 0x00;
	return (group);
}

/*custom split for readline input to nodes*/
char	**ft_split_v2(char const *s, int *d, int c)
{
	char	**split;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	split = (char **)malloc(sizeof(char *) * (group_count(d, c) + 1));
	if (split == NULL)
		return (NULL);
	while (d[i] != -1)
	{
		while (d[i] == c && d[i] != -1)
			i++;
		if (d[i] != -1)
		{
			split[j] = group_dup(&d[i], &s[i], c);
			j++;
		}
		while (d[i] != c && d[i] != -1)
			i++;
	}
	split[j] = 0x00;
	return (split);
}
