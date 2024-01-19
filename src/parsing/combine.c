/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:05:50 by wyap              #+#    #+#             */
/*   Updated: 2024/01/09 15:23:25 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*combine_w_prev(t_node *ptr)
{
	t_node	*tmp;

	printf("\n\tcombine with prev mark\n");
	//merge current node with previous node
	if (ptr->prev && (!ft_strcmp(ptr->prev->attr, "none") || !ft_strcmp(ptr->prev->attr, "space")))
	{
			ptr->prev->content = ft_strjoin(ptr->prev->content, ptr->content);
			ptr->prev->next = ptr->next;
			if (ptr->next)
				ptr->next->prev = ptr->prev;
			tmp = ptr;
			ptr = ptr->prev;
			// free(tmp);
			free_node(tmp);
	}
	return (ptr);
}

t_node	*combine_w_next(t_node *ptr)
{
	t_node	*tmp;

	printf("\n\tcombine with next mark\n");
	tmp = ptr->next;
	if (tmp && (!ft_strcmp(tmp->attr, "none") || !ft_strcmp(tmp->attr, "space")))
	{
		ptr->content = ft_strjoin(ptr->content, tmp->content);
		ptr->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = ptr;
		// tmp = ptr->next;
		// free(tmp);
		free_node(tmp);
	}
	return (ptr);
}

/*
* combine nodes that is not operator or commands
* !!: DIRECT LEAK DETECTED IN WSL
*/
void	combine_nodes(t_node **lst_cmd)
{
	t_node	*ptr;

	ptr = *lst_cmd;
	while (ptr)
	{
		if (!ft_strcmp(ptr->attr, "none") || !ft_strcmp(ptr->attr, "space"))
			ptr = combine_w_prev(ptr);
		else if (!ft_strcmp(ptr->attr, "builtin") || (!ft_strcmp(ptr->attr, "operator") && ptr->next && ft_strcmp(ptr->next->attr, "none")))
			ptr = combine_w_next(ptr);
		if (ptr && ptr->next)
			ptr = ptr->next;
		else
			break ;
	}
}

/*code if further attr classification is implemented*/
	// else if (!ft_strcmp(ptr->attr, "builtin") || (!ft_strcmp(ptr->attr, "rdr") && ptr->next && ft_strcmp(ptr->next->attr, "none")))

/*
* combine nodes that is not operator or commands
* !!: DIRECT LEAK DETECTED IN WSL
*/
// void	combine_nodes(t_node **lst_cmd)
// {
// 	t_node	*ptr;
// 	t_node	*tmp;
// 	t_node	*tmp2;

// 	ptr = *lst_cmd;
// 	while (ptr)
// 	{
// 		if (!ft_strcmp(ptr->attr, "none") || !ft_strcmp(ptr->attr, "space"))
// 		{
// 			//merge current node with previous node
// 			if (ptr->prev && (!ft_strcmp(ptr->prev->attr, "none") || !ft_strcmp(ptr->prev->attr, "space")))
// 			{
// 					ptr->prev->content = ft_strjoin(ptr->prev->content, ptr->content);
// 					ptr->prev->next = ptr->next;
// 					if (ptr->next)
// 						ptr->next->prev = ptr->prev;
// 					tmp = ptr;
// 					ptr = ptr->prev;
// 					// free(tmp);
// 					free_node(tmp);
// 			}
// 		}
// 		else if (!ft_strcmp(ptr->attr, "builtin") || !ft_strcmp(ptr->attr, "operator"))
// 		{
// 			//merge current node with next node
// 			tmp2 = ptr->next;
// 			if (tmp2 && (!ft_strcmp(tmp2->attr, "none") || !ft_strcmp(tmp2->attr, "space")))
// 			{
// 					ptr->content = ft_strjoin(ptr->content, tmp2->content);
// 					ptr->next = tmp2->next;
// 					if (tmp2->next)
// 						tmp2->next->prev = ptr;
// 					// tmp = ptr->next;
// 					// free(tmp2);
// 					free_node(tmp2);
// 			}
// 		}
// 		if (ptr && ptr->next)
// 			ptr = ptr->next;
// 		else
// 			break ;
// 	}
// }

// void	free_node(t_node *node)
// {
// 	// free(node->attr);
// 	free(node->content);
// 	free(node->next);
// 	free(node->prev);
// 	// free(node->quote_type);
// 	free(node);
// }

/*combine nodes that is not operator or commands*/
// void	combine_nodes(t_node **lst_cmd)
// {
// 	t_node 	*ptr;
// 	t_node	*tmp;

// 	ptr = *lst_cmd;
// 	while (ptr)
// 	{
// 		if (!ft_strcmp(ptr->attr, "none") || !ft_strcmp(ptr->attr, "space"))
// 		{
// 			if (ptr->prev && (!ft_strcmp(ptr->prev->attr, "none") || !ft_strcmp(ptr->prev->attr, "space")))
// 			{
// 					ptr->prev->content = ft_strjoin(ptr->prev->content, ptr->content);
// 					ptr->prev->next = ptr->next;
// 					if (ptr->next)
// 						ptr->next->prev = ptr->prev;
// 					tmp = ptr;
// 					ptr = ptr->prev;
// 					// free(tmp);
// 					free_node(tmp);
// 			}
// 		}
// 		else if (!ft_strcmp(ptr->attr, "builtin") || !ft_strcmp(ptr->attr, "operator"))
// 		{
// 			if (ptr->next && (!ft_strcmp(ptr->next->attr, "none") || !ft_strcmp(ptr->next->attr, "space")))
// 			{
// 					ptr->content = ft_strjoin(ptr->content, ptr->next->content);
// 					ptr->next = ptr->next->next;
// 					if (ptr->next->next)
// 						ptr->next->next->prev = ptr;
// 					tmp = ptr->next;
// 					// free(tmp);
// 					free_node(tmp);
// 			}
// 		}
// 		if (ptr && ptr->next)
// 			ptr = ptr->next;
// 		else
// 			break ;
// 	}
// }
