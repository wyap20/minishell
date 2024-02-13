/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:10:48 by atok              #+#    #+#             */
/*   Updated: 2023/11/26 01:10:48 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
-1: EOL
0: unassigned
1: single quote & chars inside quotes
2: double single quote ('')
3: double double quote ("")
4: single right arrow (>)
5: single left arrow (<)
6: double right arrow (>>)
7: double left arrow (<<)
8: pipe (|)
9: other characters
10: space
11: double quote & chars inside quotes
*/

/*set all element as 0 before indexing*/
int	*ft_setup(char *str)
{
	int	len;
	int	i;
	int	*id;

	i = 0;
	len = (int)ft_strlen(str);
	id = (int *)malloc(sizeof(int) * (len + 1));
	id[len] = -1;
	while (i < len)
	{
		id[i] = 0;
		i++;
	}
	return (id);
}
	// printf("setup:\n");
	// for (i = 0; id[i] != -1 ; i++)
	// 	printf("%d,",id[i]);
	// printf("%d\n",id[i]);

int	*ft_quote_pair(int *out, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] == '\'')
		{
			out[i] = 2;
			out[i + 1] = 2;
		}
		if (str[i] == '\"' && str[i + 1] == '\"')
		{
			out[i] = 3;
			out[i + 1] = 3;
		}
		i++;
	}
	return (out);
}

int	*ft_index_uniquote(int *out, char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '\'')
		{
			c = str[i];
			out[i] = 1;
			i++;
			while (str[i] != c)
				out[i++] = 1;
			out[i] = 1;
			c = 0x00;
		}
		if (str[i] == '\"')
		{
			c = str[i];
			out[i] = 11;
			i++;
			while (str[i] != c)
				out[i++] = 11;
			out[i] = 11;
			c = 0x00;
		}
		i++;
	}
	return (out);
}

int	*ft_index_left_arrow(int *out, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (out[i] == 0)
			{
				out[i] = 7;
				i++;
				out[i] = 7;
			}
			if (out[i + 1] != -1)
				i++;
		}
		if (str[i] == '<' && str[i + 1] != '<')
		{
			if (out[i] == 0)
				out[i] = 5;
		}
		i++;
	}
	return (out);
}

int	*ft_index_right_arrow(int *out, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			if (out[i] == 0)
			{
				out[i] = 6;
				i++;
				out[i] = 6;
			}
			if (out[i + 1] != -1)
				i++;
		}
		if (str[i] == '>' && str[i + 1] != '>')
			if (out[i] == 0)
				out[i] = 4;
		i++;
	}
	return (out);
}

int	*ft_index_pipe(int *out, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '|')
		{
			if (out[i] == 0)
				out[i] = 8;
		}
		i++;
	}
	return (out);
}

int	*ft_index_space(int *out, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == ' ')
		{
			if (out[i] == 0)
				out[i] = 10;
		}
		i++;
	}
	return (out);
}

int	*ft_index_others(int *out)
{
	int	i;

	i = 0;
	while (out[i] != -1)
	{
		if (out[i] == 0)
			out[i] = 9;
		i++;
	}
	return (out);
}

int	*ft_index(char *cmd_buf)
{
	int	*out;

	out = ft_setup(cmd_buf);
	out = ft_quote_pair(out, cmd_buf);
	out = ft_index_uniquote(out, cmd_buf);
	out = ft_index_left_arrow(out, cmd_buf);
	out = ft_index_right_arrow(out, cmd_buf);
	out = ft_index_pipe(out, cmd_buf);
	out = ft_index_space(out, cmd_buf);
	out = ft_index_others(out);
	return (out);
}
	// int i = 0;
	// while (out[i] != -1)
	// {
	// 	printf("%d,",out[i]);
	// 	i++;
	// }
	// printf ("%d\n",out[i]);