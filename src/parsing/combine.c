/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:05:50 by wyap              #+#    #+#             */
/*   Updated: 2024/01/30 22:12:26 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*make_rdr_group(t_node *ptr)
{
	t_node	*tmp;
	t_node	*tmp2;
	char	*content_ptr;

	printf("\n\tcombine rdr mark\n");
	tmp = ptr->next;
	while (tmp && !ft_strcmp(tmp->attr, "rdr_sub"))
	{
		content_ptr = ptr->content;
		ptr->content = ft_strjoin(ptr->content, " ");
		free(content_ptr);
		content_ptr = ptr->content;
		ptr->content = ft_strjoin(ptr->content, tmp->content);
		free(content_ptr);
		ptr->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = ptr;
		tmp2 = tmp;
		tmp = tmp->next;
		free_node(tmp2);
	}
	return (ptr);
}

t_node	*make_builtin_grp(t_node *ptr)
{
	t_node	*tmp;
	char	*content_ptr;

	printf("\n\tcombine builtin mark\n");
	tmp = ptr->next;
	if (tmp && !ft_strcmp(tmp->attr, "builtin_sub"))
	{
		content_ptr = ptr->content;
		ptr->content = ft_strjoin(ptr->content, tmp->content);
		free(content_ptr);
		ptr->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = ptr;
		free_node(tmp);
	}
	return (ptr);
}

t_node	*combine_w_prev(t_node *ptr)
{
	t_node	*tmp;
	char	*content_ptr;

	// printf("\n\tcombine with prev mark\n");
	//merge current node with previous node
	if (ptr->prev && (!ft_strcmp(ptr->prev->attr, "none") || !ft_strcmp(ptr->prev->attr, "space")))
	{
			content_ptr = ptr->prev->content;
			ptr->prev->content = ft_strjoin(ptr->prev->content, ptr->content);
			free(content_ptr);
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
	char	*content_ptr;

	// printf("\n\tcombine with next mark\n");
	tmp = ptr->next;
	if (tmp && (!ft_strcmp(tmp->attr, "none") || !ft_strcmp(tmp->attr, "space")))
	{
		content_ptr = ptr->content;
		ptr->content = ft_strjoin(ptr->content, tmp->content);
		free(content_ptr);
		ptr->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = ptr;
		// tmp = ptr->next;
		// free(tmp);
		free_node(tmp);
	}
	return (ptr);
}

void	set_rdr_nodes(t_node **lst_cmd)
{
	t_node	*ptr;
	// char	*tmp;

	ptr = *lst_cmd;
	// tmp = NULL;
	while (ptr)
	{
		if (!ft_strcmp(ptr->attr, "rdr") && ptr->next && ptr->next->next && !ft_strcmp(ptr->next->attr, "space") && !ft_strcmp(ptr->next->next->attr, "none"))
		{
			ptr->next->attr = "rdr_sub";
			ptr->next->next->attr = "rdr_sub";
			ptr = ptr->next->next->next;
		}
		else if ((!ft_strcmp(ptr->attr, "rdr") && ptr->next && !ft_strcmp(ptr->next->attr, "none"))) 
		{
			// tmp = ptr->next->content;
			// ptr->next->content = ft_strjoin(ptr->next->content, " ");
			// free(tmp);
			ptr->next->attr = "rdr_sub";
			ptr = ptr->next->next;
		}
		else
			ptr = ptr->next;
		if (ptr && !ft_strcmp(ptr->attr, "space") && !ft_strcmp(ptr->prev->attr, "rdr_sub"))
		{
			ptr->attr = "rdr_sub";
			ptr = ptr->next;
		}
	}
}

void	set_builtin_nodes(t_node **lst_cmd)
{
	t_node *ptr;

	ptr = *lst_cmd;
	while(ptr)
	{
		if (!ft_strcmp(ptr->attr, "builtin") && ptr->next && (!ft_strcmp(ptr->next->attr, "none") || !ft_strcmp(ptr->next->attr, "builtin")))
		{
			ptr->next->attr = "builtin_sub";
			ptr = ptr->next->next;
		}
		else
			ptr = ptr->next;
	}
}

/*
* combine nodes that is not operator or commands
*/
void	combine_nodes(t_node **lst_cmd)
{
	t_node	*ptr;

	ptr = *lst_cmd;
	while (ptr)
	{
		if (!ft_strcmp(ptr->attr, "rdr") && ptr->next && !ft_strcmp(ptr->next->attr, "rdr_sub"))
			ptr = make_rdr_group(ptr);
		else if (!ft_strcmp(ptr->attr, "builtin") && ptr->next && !ft_strcmp(ptr->next->attr, "builtin_sub"))
			ptr = make_builtin_grp(ptr);
		else if (!ft_strcmp(ptr->attr, "none") || !ft_strcmp(ptr->attr, "space"))
			ptr = combine_w_prev(ptr);
		// else if (!ft_strcmp(ptr->attr, "builtin") || (!ft_strcmp(ptr->attr, "operator") && ptr->next && ft_strcmp(ptr->next->attr, "none")))
		else if (!ft_strcmp(ptr->attr, "builtin") || ((!ft_strcmp(ptr->attr, "rdr") || !ft_strcmp(ptr->attr, "pipe")) && ptr->next && ft_strcmp(ptr->next->attr, "none")))
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
