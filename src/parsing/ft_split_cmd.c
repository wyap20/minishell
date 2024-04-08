/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:09:44 by atok              #+#    #+#             */
/*   Updated: 2024/02/20 18:09:44 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
1: initial index (before replaced by other values)
2: single quote
3: space
4: double quote 
-1: NULL (end of string)
*/

/*initialize index array with placeholder values
to prevent reading as NULL resulting in SEGV*/
int	*ft_setup_cmd_id(char *str)
{
	int	*id;
	int	len;
	int	i;

	i = 0;
	len = (int)ft_strlen(str);
	id = (int *)malloc(sizeof(int) * (len + 1));
	id[len] = -1;
	while (i < len)
	{
		id[i] = 1;
		i++;
	}
	return (id);
}

/*set space index in int array*/
int	*ft_set_sp(int *id, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == ' ')
			id[i] = 3;
		i++;
	}
	return (id);
}

/*set quotes index in int array*/
int	*ft_set_qt(int *id, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '\'')
			id[i] = 2;
		else if (str[i] == '\"')
			id[i] = 4;
		i++;
	}
	return (id);
}

/*made it shorter but left it commented out*/
int	*ft_expand_qt(int *id)
{
	int	i;

	i = 0;
	while (id[i] != -1)
	{
		if (id[i] == 4)
			i = ft_fill_in(id, i, 4);
		else if (id[i] == 2)
			i = ft_fill_in(id, i, 2);
		i++;
	}
	return (id);
}

	// for(int i = 0; i < (int)ft_strlen(str) + 1;i++)
	// 	printf("%d ",id[i]);
	// printf("\n");
	// for(int i = 0; i < (int)ft_strlen(str) ;i++)
	// 	printf("%c ",str[i]);
	// printf("\n");

/*split node->content*/
char	**ft_split_cmds(char *str)
{
	int		*id;
	char	**output;
	int		i;

	i = 0;
	id = ft_setup_cmd_id(str);
	id = ft_set_sp(id, str);
	id = ft_set_qt(id, str);
	id = ft_expand_qt(id);
	output = ft_split_v2(str, id, 3);
	while (output[i] != 0x00)
		ft_trim(output[i++]);
	free(id);
	return (output);
}
	// printf("\n");
	// while (output[i] != 0x00)
	// {
	// 	printf("\toutput[%d]: %s\n", i, output[i]);
	// 	i++;
	// }
	// //----------
	// i = 0;
