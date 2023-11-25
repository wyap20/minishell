/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 20:32:27 by atok              #+#    #+#             */
/*   Updated: 2023/11/25 20:32:27 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_len(char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
		i++;
	
	return (i);
}

int check(char c)
{
	char *delim = " |<>";
	int i = 0;
	while (delim[i] != 0x00)
	{
		if (delim[i] == c)
			return 1;
		i++;
	}
	return 0;
}

int *ft_index(char *str)
{
	int len;

	len = ft_len(str);
	printf("%d\n",len);
	int *id;

	id = (int*)malloc(sizeof(int) * (len + 1));
	id[len] = -1;

	int i;
	int x;
	char c;

	i = 0;
	x = 0;
	while (str[i] != 0x00)
	{
		if (i > 0 && str[i] == str[i - 1])
			x--;
		if (check(str[i]) == 1)
			x++;
		id[i] = x;
		if (check(str[i]) == 0)
			id[i] = 0;
		if (str[i] == '\'' || str[i] == '\"')
		{
			x++;
			id[i] = x;
			c = str[i];
			i++;
			while(str[i] != c)
			{
				id[i] = x;
				i++;
			}
			id[i] = x;
			c = 0x00;
		}
		i++;
	}
	return (id);
}
// '| grep <>"Mov '
int main (void)
{
	// char str[] = "ls | grep Mov | wc -c";
	char str[] = "ls<< \'| grep <>\"Mov \' | <wc> \"\'\" \'test\'\'ting\'-c";
	// char str[] = "echo 'test'\"ting\"";
	// char str[] = "echo \"test\"\"ting\"";
	int *out = ft_index(str);

	// printf("%c\n",str[20]);

	int i = 0;
	while(out[i] != -1)
	// while(i < 22)
	{
		printf("%d,",out[i]);
		i++;
	}
	printf("\n");
	free(out);
	return (0);
}

// int main (void)
// {
// 	int index[11];
// 	index[10] = -1;
// 	int i = 0;
// 	while (index[i] != -1)// && i <= 10)
// 		i++;
// 	printf("%i\n",i);
// 	return 0;
// }