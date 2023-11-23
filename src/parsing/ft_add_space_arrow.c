/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space_arrow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:14:48 by atok              #+#    #+#             */
/*   Updated: 2023/11/23 20:23:21 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int check_arrow_side (char *str, int i, int c) // count the space needed
{
	int x;

	x = 0;
	if (str[i - 1] != ' ')
		x++;
	if (str[i + 1] == c) //if next one is same // skip over
		i++;
	if (str[i + 1] != ' ')
		x++;
	return (x);

}

int loop_to_closed (char *str, int i, char c)
{
	while (str[i] != c)
		i++;
	return i;
}

int find_arrow(char *str) //find arrow that need space
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
		if(str[i] == '<' || str[i] == '>')
		{
			tmp += check_arrow_side(str,i,str[i]);
			if (str[i] == str[i + 1]) // skip over if same
			i += 2; 
		}
		i++;
	}
	return (tmp);
}

char *ft_add_space_arrow(char *str)
{
	int p = find_arrow(str);
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
		if (str[i] == '<' || str[i] == '>')  // << & <> & < & > // tripple arrow handeled in check_arrow
		{
			if (str[i - 1] != ' ')// && str[i - 1] != str[i]) ls<< <>cat>
			{
				add[j] = ' ';
				j++;
				add[j] = str[i];
				// j++;
				// i++;
				if (str[i] == str[i + 1]) 
				{
					add[j] = str[i];
					j++;
					i++;
				}
				if (str[i] != str[i + 1] && str[i + 1] != ' ')
				{
					add[j] = str[i];
					j++;
					i++;
					add[j] = ' ';
					j++;
				}
			}
		}
		// if (str[i] == '<' && str[i + 1] == '<') // <<
		// {
		// 	if (str[i - 1] != ' ')
		// 	{
		// 		add[j] = ' ';
		// 		j++;
		// 	}
		// 	add[j] = str[i];
		// 	i++;
		// 	j++;
		// 	add[j] = str[i];

		// }
		//WIP
		// if (str[i] == '>' && str[i + 1] == '>') // >>
		// if (str[i] == '<' && str[i + 1] != '<') // <>
		// if (str[i] == '>' && str[i + 1] != '<') // ><
		// if (str[i] == '<' && str[i + 1] != '<' && str [i - 1 != '<']) // <
		// if (str[i] == '>' && str[i + 1] != '>' && str [i - 1 != '>']) // >
		add[j] = str[i];
		i++;
		j++;
	}
	return (add);
}

int main (void)
{
	// char str[] = "|ls\"| | \'|cat|c\"t| | | |zz|";
	// char str[] = "ls<<\'| grep <>\"Mov \'| <wc> \"\'\" -c";
	char str[] = "ls<< \'| grep <>\"Mov \' | <wc> \"\'\" -c";
	// char str[] = "ls<<>><cat>";
	int i = 0;
	char *add = ft_add_space_arrow(str);

	printf("%s\n", add);
	
	return (0);
}
