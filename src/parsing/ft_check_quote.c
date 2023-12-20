/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:41:32 by atok              #+#    #+#             */
/*   Updated: 2023/12/20 14:02:28 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int loop_to_pair(char *str, int i, int qt)
{
	while (str[i] != 0x00 || str[i] != qt) // && or ||??
	{
		// if (str[i] == qt)
		// {
		// 	if (str[i + 1] == ' ')
		// 		return (i);
		// 	else str[i + 1] == qt
		// 		i++;
		// } 
		if (str[i] == 0x00)
		{
			printf("Error %c quote\n", qt); // perror():?
			exit(1);
		}
		i++;
	}
	return(-2);
}

int ft_check_quote(char *str)
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
			// while (str[i] != '\'')
			// {
			// 	if (str[i] == '\'')
			// 		break;
			// 	if (str[i] == 0x00)
			// 	{
			// 		printf("Error single quote\n"); // perror():?
			// 		return(1);
			// 	}
			// 	i++;
			// }
		}
		if (str[i] == '\"')
		{	
			i++;
			i = loop_to_pair(str,i,'\"');
			i++;
			// while (str[i] != '\"')
			// {
			// 	if (str[i] == '\"')
			// 		break;
			// 	if (str[i] == 0x00)
			// 	{
			// 		printf("Error double quote\n"); // perror():?
			// 		return(1);
			// 	}
			// 	i++;
			// }
		}
		i++;
	}
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