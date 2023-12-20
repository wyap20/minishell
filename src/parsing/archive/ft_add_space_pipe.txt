/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:54:46 by atok              #+#    #+#             */
/*   Updated: 2023/11/23 20:03:30 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int check_pipe_side (char *str, int i) // count the space needed
{
	int c;

	c = 0;
	if (str[i + 1] == '|') // handle ||
	{
		printf("|| located\n");
		exit(1);
	}
	if (str[i - 1] != ' ')
		c++;
	if (str[i + 1] != ' ')
		c++;
	return (c);

}

int loop_to_closed (char *str, int i, char c)
{
	while (str[i] != c)
		i++;
	return i;
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
			i = loop_to_closed(str,i + 1,'\'') + 1;
			// i++;
			// while(str[i] != '\'') // || str[i] != 0x00) already verified for closed quotes
			// 	i++;
			// i++;
		}
		if(str[i] == '\"')
		{
			i = loop_to_closed(str,i + 1,'\"') + 1;
			// i++;
			// while(str[i] != '\"')// || str[i] != 0x00)
			// 	i++;
			// i++;
		}
		if(str[i] == '|')
			tmp += check_pipe_side(str,i);
		i++;
	}
	return (tmp);
}

char *ft_add_space_pipe(char *str)
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
		if (str[i] == '\'')
		{
			add[j] = str[i];
			i++;
			j++;
			while (str[i] != '\'')
			{
				add[j] = str[i];
				i++;
				j++;
			}
			add[j] = str[i];
			i++;
			j++;
		}	
		if (str[i] == '\"')
		{
			add[j] = str[i];
			i++;
			j++;
			while (str[i] != '\"')
			{
				add[j] = str[i];
				i++;
				j++;
			}
			add[j] = str[i];
			i++;
			j++;
		}
		if (str[i] == '|')
		{
			if (str[i - 1] != ' ')
			{
				add[j] = ' ';
				j++;
			}
			add[j] = '|';
			j++;
			if (str[i + 1] != ' ') 
			{
				add[j] = ' ';
				j++;
			}
			i++;
		}
		add[j] = str[i];
		i++;
		j++;
	}
	return (add);
}

int main (void)
{
	// char str[] = "|ls\"| | \'|cat|c\"t| | | |zz|";
	// char str[] = "ls \'| grep \"Mov \'| wc \"\'\" -c";
	// char str[] = "ls|\'| gre||p \"Mov \'|wc|\"\'\"|-c";
	char str[] = "ls| \'| gre||p \"Mov \'|wc| \"\'\" |-c";
	int i = 0;
	char *add = ft_add_space_pipe(str);

	printf("%s\n", add);
	
	return (0);
}

// need to add space to quote first to work