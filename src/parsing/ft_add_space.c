/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:54:46 by atok              #+#    #+#             */
/*   Updated: 2023/11/22 20:55:58 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int check_pipe_side (char *str, int i) // count the space needed
{
	int c;

	c = 0;
	if (str[i + 1] == '|') // handle ||
		exit(1);
	if (str[i - 1] != ' ')
		c++;
	if (str[i + 1] != ' ')
		c++;
	return (c);

}

int find_pipe(char *str) //find pipe that need space
{
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == '\'')
		{
			i++;
			while(str[i] != '\'' || str[i] != 0x00)
				i++;
			i++;
		}
		if(str[i] == '\"')
		{
			i++;
			while(str[i] != '\'' || str[i] != 0x00)
				i++;
			i++;
		}
		if(str[i] == '|')
			tmp += check_pipe_side(str,i);
		i++;
	}
	return (tmp);
}

char *ft_add_space(char *str)
{
	int p = find_pipe(str);
	char *add = malloc(sizeof (char *) * p + 1); // char *
	add[p] = 0x00;
	
	int i;
	int j;
	i = 0;
	j = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '\'' || str[i] != '\"')
		{
			add[j] = str[i];
			i++;
			j++;
		}	
		add[j] = str[i];
		i++;
		j++;
	}
	return (add);
}

int main (void)
{
	char str[] = "ls \'| grep \"Mov \'| wc \"\'\" -c";
	int i = 0;
	char *add = ft_add_space(str);

	printf("%s\n", add);
	
	return (0);
}
