/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:41:32 by atok              #+#    #+#             */
/*   Updated: 2023/12/20 16:50:34 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_check_quote(char *str)
{
	int i;

	i = 0;
	while(str[i] != 0x00 && i > 0)
	{
		if (str[i] == '\'')
		{	
			i++;
			i = loop_to_pair(str,i,'\'');
			i++;
		}
		if (str[i] == '\"')
		{	
			i++;
			i = loop_to_pair(str,i,'\"');
			i++;
		}
		i++;
	}
	if (i < 0)
		return (-1);
	return (0);
}

// int main (void)
// {
// 	// char str[] = "echo \"hello \"world\'"; //0 = no error
// 	// char str[] = "ls \'| grep \"Mov \'| wc \"\'\" -c"; //0 = no error
// 	// char str[] = "ls \'| grep \"Mov \'| wc \'\" -c";// single quote error
// 	// char str[] = "ls \'| grep \"Mov \'| wc \"\' -c";// double quote error
// 	int i = ft_check_quote(str);
// 	//printf("%d\n",count(str));
// 	printf("%d\n",i);
// 	return (0);
// }