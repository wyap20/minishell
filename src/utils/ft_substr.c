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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s || len == 0)
		return (ft_strdup(""));
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (*s && i < len)
	{
		if (s[start] == 0x00)
			break ;
		if (start >= ft_strlen(s))
			return (ft_strdup(""));
		sub[i++] = s[start++];
	}
	sub[i] = 0x00;
	return (sub);
}
