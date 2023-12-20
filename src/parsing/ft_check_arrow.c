/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:33:43 by atok              #+#    #+#             */
/*   Updated: 2023/12/20 17:08:10 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_arrow(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '\'')
		{	
			i++;
			i = loop_to_pair(str, i, '\'') + 1;
		}
		if (str[i] == '\"')
		{	
			i++;
			i = loop_to_pair(str, i, '\"') + 1;
		}
		if (str[i] == '<' || str[i] == '>')
			if (str[i + 1] == str[i] && str[i + 2] == str[i])
				return (-1);
		i++;
	}
	return (0);
}
