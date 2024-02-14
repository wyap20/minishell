/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_quote_arrw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:54:43 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 16:09:49 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	*label_quote(int *out, char *str, char quote, int *i)
{
	int	num;

	num = 0;
	if (quote == '\'')
	{
		out[*i] = 1;
		num = 1;
	}
	if (quote == '\"')
	{
		out[*i] = 11;
		num = 11;
	}
	(*i)++;
	while (str[*i] != quote)
		out[(*i)++] = num;
	out[*i] = num;
	quote = 0x00;
	return (out);
}

int	*ft_index_quote(int *out, char *str)
{
	int		i;

	i = -1;
	while (str[++i] != 0x00)
	{
		if (str[i] == '\'' || str[i] == '\"')
			out = label_quote(out, str, str[i], &i);
	}
	return (out);
}

// int	*ft_index_quote(int *out, char *str)
// {
// 	int		i;
// 	char	c;

// 	i = -1;
// 	while (str[++i] != 0x00)
// 	{
// 		if (str[i] == '\'')
// 		{
// 			c = str[i];
// 			out[i] = 1;
// 			i++;
// 			while (str[i] != c)
// 				out[i++] = 1;
// 			out[i] = 1;
// 			c = 0x00;
// 		}
// 		if (str[i] == '\"')
// 		{
// 			c = str[i];
// 			out[i] = 11;
// 			i++;
// 			while (str[i] != c)
// 				out[i++] = 11;
// 			out[i] = 11;
// 			c = 0x00;
// 		}
// 	}
// 	return (out);
// }

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
