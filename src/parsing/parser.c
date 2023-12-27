/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:27:27 by wyap              #+#    #+#             */
/*   Updated: 2023/12/27 16:15:13 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*ft_parse(t_node *lst_cmd ,char *cmd_buf)
{
	int	i;
	int len;
	int start;
	int index;
	int	*int_array;
	char *node;

	// (void) lst_cmd;
	i = 1;
	len = 0;
	start = 0;
	int_array = ft_index(cmd_buf);
	index = int_array[0];
	//first substr
	while (int_array[i] == index)
		i++;
	node = ft_substr(cmd_buf, 0, i);
	printf("parse 1st node:%s#\ni: %d\n", node, i);
	index = int_array[i];
	//get remaining substr; need start and len
	while (int_array[i] != -1)
	{
		index = int_array[i];
		if (int_array[i] == index)
		{
			i++;
			len++;
		}
		if (int_array[i] != index)
		{
			start = i - len;
			node = ft_substr(cmd_buf, start, len);
			printf("parse node:%s#\n", node);
			len = 0;
		}
	}
	//lstaddback substr
	//free (int_array);
	return (lst_cmd);
}