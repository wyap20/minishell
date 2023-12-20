/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:17:16 by atok              #+#    #+#             */
/*   Updated: 2023/12/20 14:13:09 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *ft_check_key(char* str, char* key)
{
	int i = 0;
	int j;
	while (str[i] != 0x00)
	{
		j = 0;
		if (str[i] == key[j])
		{
			i++;
			j++;
		}
		i++;
	}
	return(str);
}

int main (void)
{
	char *str = "echo me$USERme";
	char *key = "$USER";
}