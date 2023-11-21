/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:59:19 by wyap              #+#    #+#             */
/*   Updated: 2022/10/07 17:59:19 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*tmp;

	i = ft_strlen(s1);
	tmp = (char *)malloc((i + 1) * sizeof(char));
	if (!tmp)
		return (0);
	i = 0;
	while (s1[i] != 0x00)
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = 0x00;
	return (tmp);
}
