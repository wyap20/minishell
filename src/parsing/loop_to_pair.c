/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_to_pair.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:33:27 by wyap              #+#    #+#             */
/*   Updated: 2023/12/20 16:43:28 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
			return (-99);
		}
		i++;
	}
	return (i);
}