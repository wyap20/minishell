/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:46:10 by wyap              #+#    #+#             */
/*   Updated: 2022/10/09 21:46:10 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	sstrlen(char const *str)
{
	int	len;

	len = 0;
	while (str[len] != 0x00)
		len++;
	return (len);
}

char	*sstrdup(const char *src)
{
	char	*dup;
	int		i;
	int		len;

	len = 0;
	while (src[len])
		len++;
	dup = (char *) malloc(sizeof(char) * (len + 1));
	if (dup == (NULL))
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = 0x00;
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ss;
	size_t		slen;

	if (len == 0 || s == NULL)
		return (sstrdup(""));
	if (start >= sstrlen(s))
		return (sstrdup(""));
	ss = (char *)malloc((len + 1) * sizeof(char));
	if (ss == NULL)
		return (NULL);
	slen = 0;
	while (s[start] != 0x00 && slen < len)
	{
		ss[slen] = s[start];
		start++;
		slen++;
	}
	ss[slen] = 0x00;
	return (ss);
}
