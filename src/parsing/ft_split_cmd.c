/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:09:44 by atok              #+#    #+#             */
/*   Updated: 2024/02/20 18:09:44 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int *ft_setup_cmd_id(char *str)
{
	int *id;
	int	len;
	int	i;

	i = 0;
	len = (int)ft_strlen(str);
	id = (int *)malloc(sizeof(int) * (len + 1));
	id[len] = -1;
	while (i < len)
	{
		id[i] = 1;
		i++;
	}
	return (id);
}

int *ft_set_sp(int *id, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == ' ')
			id[i] = 3;
		i++;
	}
	return (id);
}

int *ft_set_qt(int *id, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '\'')
			id[i] = 2;
		else if (str[i] == '\"')
			id[i] = 4;
		i++;
	}
	return (id);
}

/* uncomment tmp to allow for open quotes */
int ft_get_b(int *id, int a, int q)
{
	int flag;
	// int tmp;

	// tmp = a;
	flag = 0;
	while(id[a] != -1)
	{
		if (id[a] == q)
			flag++;
		if (flag == 2)
			break;
		a++;
	}
	// if (flag == 1)
	// 	return (tmp);
	return (a);
}

int ft_fill_in(int *id, int i, int q)
{
	int a;
	int b;

	a = i;
	b = ft_get_b(id,a,q);
	while (a != b)
	{
		id[a] = q;
		a++;
	}
	return (a);
}

/* made it shorter but left it commented out */
int *ft_expand_qt(int *id)
{
	int i;
	// int a;
	// int b;

	i = 0;
	while (id[i] != -1)
	{
		if (id[i] == 4)
		{
			i = ft_fill_in(id,i,4);
			// a = i;
			// b = ft_get_b(id,a,4);
			// while (a != b)
			// {
			// 	id[a] = 4;
			// 	a++;
			// }
			// i = a;
		}
		else if (id[i] == 2)
		{
			i = ft_fill_in(id,i,2);
			// a = i;
			// b = ft_get_b(id,a,2);
			// while (a != b)
			// {
			// 	id[a] = 2;
			// 	a++;
			// }
			// i = a;
		}
		i++;
	}
	return (id);
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

char	**ft_split_v2(char const *s,int *d, int c)
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
			// memmove(split[j]);??
				j++;
		}
		while (d[i] != c && d[i] != -1)
			i++;
	}
	split[j] = 0x00;
	return (split);
}

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
			break;
		}
		j++;
	}
	if (s[j] == '\0')
		(*i)++;
}

void ft_trim(char *s) 
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

// void	ft_trim(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	c;

// 	i = 0;
// 	while (str[i] != 0x00)
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 		{
// 			c = str[i];
// 			j = i + 1;
// 			while (str[j] != 0x00)
// 			{
// 				if (str[j] == c)
// 				{
// 					ft_memmove(str + i, str + (i + 1), ft_strlen(str + (i + 1)) + 1);
// 					ft_memmove(str + j - 1, str + (j), ft_strlen(str + (j)) + 1);
// 					i = j - 1;
// 					break ;
// 				}
// 				j++;
// 			}
// 			if(str[j] == 0x00)
// 				i++;
// 		}
// 		else
// 			i++;
// 	}
// }

char **ft_split_cmds(char *str)
{
	int		*id;
	char	**output;

	id = ft_setup_cmd_id(str);
	id = ft_set_sp(id, str);
	id = ft_set_qt(id, str);
	id = ft_expand_qt(id);
	// for(int i = 0; i < (int)ft_strlen(str) + 1;i++)
	// 	printf("%d ",id[i]);
	// printf("\n");
	// for(int i = 0; i < (int)ft_strlen(str) ;i++)
	// 	printf("%c ",str[i]);
	// printf("\n");
	output = ft_split_v2(str,id,3);
	int i = 0;
	// printf("\n");
	// while (output[i] != 0x00)
	// {
	// 	printf("\toutput[%d]: %s\n", i, output[i]);
	// 	i++;
	// }
	// //----------
	// i = 0;
	while (output[i] != 0x00)
		ft_trim(output[i++]);
	free(id);
	return (output);
}

// ' 2
// " 4
// sp 3
// NULL -1
// others 1
