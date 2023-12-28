/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:27:27 by wyap              #+#    #+#             */
/*   Updated: 2023/12/28 16:09:37 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*tokenize: add node to list*/
void	tokenize(t_node **lst_cmd, char *cmd_buf, int *int_array, int index)
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

/*parsing: split command to substring and add to list as nodes*/
void	ft_parse(t_node **lst_cmd, char *cmd_buf, int *int_array)
{
	int		index;

	index = int_array[0];
	tokenize(lst_cmd, cmd_buf, int_array, index);
	free (int_array);
	return ;
}

void	assign_attr(t_node **lst_cmd)
{
	t_node	*ptr;

	ptr = *lst_cmd;
	while (ptr)
	{
		if (ptr->content[0] == '\"')
			ptr->quote_type = "double";
		if (ptr->content[0] == '\'')
			ptr->quote_type = "single";
		if (ptr->content[0] != '\'' && ptr->content[0] != '\"')
			ptr->quote_type = "none";
		if (!ft_strcmp(ptr->content, "<<") || !ft_strcmp(ptr->content, ">>")
			|| !ft_strcmp(ptr->content, "<") || !ft_strcmp(ptr->content, ">")
			|| !ft_strcmp(ptr->content, "|"))
			ptr->attr = "operator";
		if (!ft_strcmp(ptr->content, "echo") || !ft_strcmp(ptr->content, "cd")
			|| !ft_strcmp(ptr->content, "pwd") || !ft_strcmp(ptr->content, "export")
			|| !ft_strcmp(ptr->content, "unset") || !ft_strcmp(ptr->content, "env")
			|| !ft_strcmp(ptr->content, "exit"))
			ptr->attr = "builtin";
		ptr = ptr->next;
	}
}
