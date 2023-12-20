/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:33:43 by atok              #+#    #+#             */
/*   Updated: 2023/12/20 19:55:41 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_loop_to_pair(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != c && str[*i] != 0x00)
		(*i)++;
	if (str[*i] == c)
		c = 0x00;
	if (str[*i] == 0x00)
	return;	
}

int	ft_check_arrow(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{	
			ft_loop_to_pair(str, &i, str[i]);
		}
		if (str[i] == '<' || str[i] == '>')
			if (str[i + 1] == str[i] && str[i + 2] == str[i])
				return (-1);
		i++;
	}
	return (0);
}

// int	ft_check_arrow(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != 0x00)
// 	{
// 		if (str[i] == '\'')
// 		{	
// 			i++;
// 			i = loop_to_pair(str, i, '\'') + 1;
// 		}
// 		if (str[i] == '\"')
// 		{	
// 			i++;
// 			i = loop_to_pair(str, i, '\"') + 1;
// 		}
// 		if (str[i] == '<' || str[i] == '>')
// 			if (str[i + 1] == str[i] && str[i + 2] == str[i])
// 				return (-1);
// 		i++;
// 	}
// 	return (0);
// }
