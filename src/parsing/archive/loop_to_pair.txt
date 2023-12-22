/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_to_pair.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:33:27 by wyap              #+#    #+#             */
/*   Updated: 2023/12/20 19:58:37 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// rework this to run like ft_loop_to_pair ????
// Or arhcive it 

int loop_to_pair(char *str, int i, int qt)
{
	int c = 2;
	while (str[i] != 0x00 && c == 0)
	{
		// if (c == 0)
			// return (i);
		if (str[i] == qt)
			c--;
		i++;
	}
	if (c == 1)
	{
		printf("Error1 %c quote\n", qt); // perror():?
		return(-99);
	}
	// i++;
	// if (str[i] == 0x00)
	// {
	// 	printf("Error1 %c quote\n", qt); // perror():?
	// 	return (-99);
	// }
	// else if (str[i] != 0x00)
	// {
	// 	while (str[i] != 0x00)// || str[i] != qt) // && or ||??
	// 	{
	// 		if (str[i] == qt)
	// 			return (i);
	// 		if (str[i] == 0x00)
	// 		{
	// 			printf("Error2 %c quote\n", qt); // perror():?
	// 			return (-99);
	// 		}
	// 		i++;
	// 	}
	// }
	return (i);
}