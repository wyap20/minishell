/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:36:55 by wyap              #+#    #+#             */
/*   Updated: 2022/10/18 23:36:55 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	word_count(const char *s, char c)
{
	size_t	count;
	size_t	trigger;

	count = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			trigger++;
			count++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (count);
}

char	*word_dup(const char *s1, int start, int end)
{
	int		i;
	char	*tmp;

	if (!s1)
		return (0);
	tmp = (char *)malloc((end - start + 1) * sizeof(char));
	i = 0;
	if (!tmp)
		return (0);
	while (start < end)
		tmp[i++] = s1[start++];
	tmp[i] = 0x00;
	return (tmp);
}

size_t	ft_whileloop(const char	*s, char c, char	**split)
{
	size_t	i;
	size_t	j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && k == -1)
			k = i;
		else if ((s[i] == c || i == ft_strlen(s)) && k >= 0)
		{
			split[j++] = word_dup(s, k, i);
			k = -1;
		}
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	char	**split;

	if (!s)
		return (0);
	split = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	j = ft_whileloop(s, c, split);
	split[j] = 0x00;
	return (split);
}
