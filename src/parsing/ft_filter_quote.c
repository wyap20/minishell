/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filter_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:09:56 by atok              #+#    #+#             */
/*   Updated: 2023/11/25 19:09:56 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *ft_filter_quote(char *str)
{
	int i;
	int j;
	int k;
	char c;
	char d;
	i = 0;
	while (str[i] != 0x00)
	{
		if ((str[i] == '\'' || str[i] == '\"'))// && str[i + 1] != 0x00)
		{
			if(str[i - 1] != ' ')
			{
				c = str[i];
				k = i;
				j = i + 1;
				while (str[k] != 0x00)
					str[k++] = str[j++];
				k = i;
				while(str[k++] != c )
				c = 0x00;
				k = i;
				j = i + 1;
				while (str[k] != 0x00)
					str[k++] = str[j++];
			}
			else if(str[i - 1] == ' ')
			{
				c = str[i];
				i++;
				while(str[i] != c )
					i++;
				if (str[i + 1] == c)
					i--;
				c = 0x00;
			}
		}
		i++;
	}
	return(str);
}

int main (void)
{

	// char str[] = "echo \"test\" \"ting\"";
	// char str[] = "echo \"test""ting\"";
	// char str[] = "echo\"test\"\"ting\"";
	char str[] = "echo \"test\"\"ting\"";
	char *add = ft_filter_quote(str);
	// int i;

	// i = 0;
	// while (str[i] != 0x00)
	// 	write(1, &str[i++], 1);
	// write(1, "\n", 1);

	// int i = 0;
	// while (str[i] != 0x00)
	// 	i++;
	// printf("%d\n",i);
	// printf("%ld\n", strlen(str));

	printf("%s\n", str);
	printf("%s\n", add);
	
	return (0);
}