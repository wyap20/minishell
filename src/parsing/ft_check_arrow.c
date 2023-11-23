/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:33:43 by atok              #+#    #+#             */
/*   Updated: 2023/11/23 17:47:29 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int loop_to_pair(char *str, int i, int qt)
{
	while (str[i] != 0x00 || str[i] != qt) // && or ||??
	{
		if (str[i] == qt)
			return (i);
		if (str[i] == 0x00)
		{
			printf("Error %c quote\n", qt); // perror():?
			exit(1);
		}
		i++;
	}
	return(-2);
}

int ft_check_arrow(char *str)
{
	int i;

	i = 0;
	while(str[i] != 0x00)
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
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == str[i] && str[i + 2] == str[i])
			{
				printf("Tripple %c \n", str[i]);
				exit(1);
			}
		}
		i++;
	}
	return (0);
}