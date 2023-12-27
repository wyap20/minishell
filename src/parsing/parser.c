/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:27:27 by wyap              #+#    #+#             */
/*   Updated: 2023/12/27 17:43:24 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*get remaining substr and add node to list*/
void add_back(t_node **lst_cmd, char *cmd_buf, int *int_array, int index)
{
	int		i;
	int		len;
	int		start;
	t_node	*node;

	i = 0;
	len = 0;
	start = 0;
	while (int_array[i] != -1)
	{
		if (int_array[i] == 8)
			i++;
		index = int_array[i];
		if (int_array[i++] == index)
			len++;
		if (int_array[i] != index)
		{
			start = i - len;
			node = ft_dlstnew(ft_substr(cmd_buf, start, len));
			ft_dlstadd_back(lst_cmd, node);
			len = 0;
		}
	}
}
			// printf("parse node:%s#\n", ft_substr(cmd_buf, start, len));

void	ft_parse(t_node **lst_cmd, char *cmd_buf, int *int_array)
{
	int		index;

	index = int_array[0];
	add_back(lst_cmd, cmd_buf, int_array, index);
	free (int_array);
	// print_nodes(lst_cmd);
	return ;
}
