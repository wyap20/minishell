#include "../../minishell.h"

/*part of ft_split_cmd*/

void	remove_quote(char *s, char c, int *i)
{
	int	j;

	j = *i + 1;
	while (s[j] != '\0')
	{
		if (s[j] == c)
		{
			ft_memmove(s + *i, s + (*i + 1), ft_strlen(s + (*i + 1)) + 1);
			ft_memmove(s + j - 1, s + (j), ft_strlen(s + (j)) + 1);
			*i = j - 1;
			break ;
		}
		j++;
	}
	if (s[j] == '\0')
		(*i)++;
}

void	ft_trim(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			remove_quote(s, c, &i);
		}
		else
			i++;
	}
}
