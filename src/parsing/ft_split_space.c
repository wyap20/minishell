/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:54:46 by atok              #+#    #+#             */
/*   Updated: 2023/12/20 14:07:15 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char delim(char c)
{
	if(c == ' ' || c == 9 || c == '\n')
		return (c);
	else 
		return(0);
}

int wcount(char *str)
{
	int i = 0;
	int w = 0;

	while (str[i] != 0x00)
	{
		while (str[i] == delim(str[i]) && str[i] != 0x00) // while its delimiter
			i++;
		if (str[i] != delim(str[i]) && str[i] != 0x00)
			w++;
		while (str[i] != delim(str[i]) && str[i] != 0x00) // while its character
			i++;
	}
	//printf("%d\n",w);
	return (w);
}

char *dup(char *str)
{
	int len = 0;
	int i = 0;
	char *word;
	while (str[len] != delim(str[len]) && str[len] != 0x00)
		len++;
	//printf("%d\n",len);
	word = malloc(sizeof(char) * len + 1); // char
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0x00;
	return (word);
}

char **ft_split(char *str)
{
	int w = wcount(str);
	char **split = malloc(sizeof (char *) * w + 1); // char *
	split[w] = 0x00;
	
	int i;
	int j;
	while (str[i] != 0x00)
	{
		while (str[i] == delim(str[i]) && str[i] != 0x00) //while its delimiter
			i++;
		if (str[i] != delim(str[i]) && str[i] != 0x00)
		{
			split[j] = dup(&str[i]);
			j++;
		}
		while (str[i] != delim(str[i]) && str[i] != 0x00) //while its character
			i++;
	}
	return (split);
}

// int main (void)
// {
// 	char str[] = "ls \'| grep \"Mov \' | wc \"\'\" -c";
// 	int i = 0;
// 	char **split = ft_split(str);
// 	//printf("%d\n",count(str));

// 	while (split[i] != 0x00)
// 	{
// 		printf("%s\n", split[i]);
// 		i++;
// 	}
// 	return (0);
// }
