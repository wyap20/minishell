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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../minishell.h"

// int ft_len(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] != 0x00)
// 		i++;
	
// 	return (i);
// }
/*
-1: EOL
0: unassigned
1: quote & chars inside quote pair & other character
2: (none)
3: single right arrow (>)
4: single left arrow (<)
5: double right arrow (>>)
6: double left arrow (<<)
7: pipe (|)
8: space
*/

int *ft_setup(char *str)
{
	int len;

	len = (int)ft_strlen(str);
	// printf("len - %d\n",len);
	int *id;

	id = (int*)malloc(sizeof(int) * (len + 1));
	id[len] = -1;
	int i;
	i = 0;
	while (id[i] != -1)
	{
		id[i] = 0;
		i++;
	}
	return (id);
}

// int *ft_index_quote(int *out, char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] != 0x00)
// 	{
// 		if(str[i] == '\'')
// 		{
// 			out[i++] = 1;
// 			while(str[i] != '\'')
// 				out[i++] = 1;
// 			out[i] = 1;
// 		}	
// 		else if(str[i] == '\"')
// 		{
// 			out[i++] = 2;
// 			while(str[i] != '\"')
// 				out[i++] = 2;
// 			out[i] = 2;
// 		}	
// 		i++;
// 	}
// 	return (out);
// }

int *ft_index_uniquote(int *out, char *str)
{
	int i;
	char c;

	i = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			out[i] = 1;
			i++;
			while(str[i] != c)
				out[i++] = 1;
			out[i] = 1;
			c = 0x00;
		}	
		i++;
	}
	return (out);
}

int *ft_index_left_arrow(int *out, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (out[i] == 0)
			{
				out[i] = 6;
				out[i + 1] = 6;
			}
			i += 2;
		}
		if (str[i] == '<' && str[i + 1] != '<')
			if (out[i] == 0)
				out[i] = 4;
		i++;
	}
	return (out);
}

int *ft_index_right_arrow(int *out, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			if (out[i] == 0)
			{
				out[i] = 5;
				out[i + 1] = 5;
			}
			i += 2;
		}
		if (str[i] == '>' && str[i + 1] != '>')
			if (out[i] == 0)
				out[i] = 3;
		i++;
	}
	return (out);
}

int *ft_index_pipe(int *out, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == '|')
		{
			if(out[i] == 0)
				out[i] = 7;
		}
		i++;
	}
	return (out);
}

int *ft_index_space(int *out, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == ' ') 
		{
			if(out[i] == 0)
				out[i] = 8;
		}
		i++;
	}
	return (out);
}

int *ft_index_others(int *out)
{
	int i;

	i = 0;
	while (out[i] != -1)
	{
		if(out[i] == 0) 
		{
			out[i] = 1;
		}
		i++;
	}
	return (out);
}

int *ft_separate(int *out, char *str)
{
	int i;

	i = 0;
	while (out[i] != -1)
	{
		if (out[i] == 8)
			i++;
		write(1, &str[i], 1);
		if (out[i] != out[i + 1])
			write(1, "\n", 1);
		i++;
	}
	return (out);
}

int *ft_index(char *cmd_buf)
{
	int	*out;

	out = ft_setup(cmd_buf);
	// out = ft_index_quote(out, cmd_buf);
	out = ft_index_uniquote(out, cmd_buf);
	out = ft_index_left_arrow(out, cmd_buf);
	out = ft_index_right_arrow(out, cmd_buf);
	out = ft_index_pipe(out, cmd_buf);
	out = ft_index_space(out, cmd_buf);
	out = ft_index_others(out);
	// out = ft_separate(out, cmd_buf);
	// out = ft_remove_quote(out, cmd_buf);
	// printf("%c\n", cmd_buf[20]);
	int i = 0;
	while(out[i] != -1)
	{
		printf("%d,",out[i]);
		i++;
	}
	printf("%d\n",out[i]);
	return (out);
}