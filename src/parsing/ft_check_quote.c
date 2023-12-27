/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:41:32 by atok              #+#    #+#             */
/*   Updated: 2023/12/27 15:22:10 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_quote(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = 0x00;
	while (str[i] != 0x00 && c == 0x00)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i] != 0x00)
				i++;
			if (str[i] == c)
				c = 0x00;
			if (str[i] == 0x00)
				break ;
		}
		i++;
	}
	if (c != 0x00)
		return (printf("Error %c quote\n", c), -1);
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