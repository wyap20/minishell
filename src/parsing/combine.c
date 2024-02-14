/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:05:50 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 16:00:40 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*make_rdr_group(t_node *ptr)
{
	t_node	*tmp;
	t_node	*tmp2;
	char	*content_ptr;

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

// t_node	*make_builtin_grp(t_node *ptr)
// {
// 	t_node	*tmp;
// 	char	*content_ptr;

// 	printf("\n\tcombine builtin mark\n");
// 	tmp = ptr->next;
// 	if (tmp && !ft_strcmp(tmp->attr, "builtin_sub"))
// 	{
// 		content_ptr = ptr->content;
// 		ptr->content = ft_strjoin(ptr->content, tmp->content);
// 		free(content_ptr);
// 		ptr->next = tmp->next;
// 		if (tmp->next)
// 			tmp->next->prev = ptr;
// 		free_node(tmp);
// 	}
// 	return (ptr);
// }

/*merge current node with previous node*/
t_node	*combine_w_prev(t_node *ptr)
{
	t_node	*tmp;
	char	*content_ptr;

	if (ptr->prev && (!ft_strcmp(ptr->prev->attr, "none")
			|| !ft_strcmp(ptr->prev->attr, "space")))
	{
		content_ptr = ptr->prev->content;
		ptr->prev->content = ft_strjoin(ptr->prev->content, ptr->content);
		free(content_ptr);
		ptr->prev->next = ptr->next;
		if (ptr->next)
			ptr->next->prev = ptr->prev;
		tmp = ptr;
		ptr = ptr->prev;
		free_node(tmp);
	}
	return (ptr);
}

/*merge current node with next node*/
t_node	*combine_w_next(t_node *ptr)
{
	t_node	*tmp;
	char	*content_ptr;

	tmp = ptr->next;
	if (tmp && (!ft_strcmp(tmp->attr, "none")
			|| !ft_strcmp(tmp->attr, "space")))
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

void	set_rdr_nodes(t_node **lst_cmd)
{
	t_node	*ptr;

	ptr = *lst_cmd;
	while (ptr)
	{
		if (!ft_strcmp(ptr->attr, "rdr") && ptr->next && ptr->next->next
			&& !ft_strcmp(ptr->next->attr, "space") && !ft_strcmp(ptr->next->next->attr, "none"))
		{
			ptr->next->attr = "rdr_sub";
			ptr->next->next->attr = "rdr_sub";
			ptr = ptr->next->next->next;
		}
		else if ((!ft_strcmp(ptr->attr, "rdr") && ptr->next && !ft_strcmp(ptr->next->attr, "none")))
		{
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

// void	set_builtin_nodes(t_node **lst_cmd)
// {
// 	t_node *ptr;

// 	ptr = *lst_cmd;
// 	while(ptr)
// 	{
// 		if (!ft_strcmp(ptr->attr, "builtin") && ptr->next && (!ft_strcmp(ptr->next->attr, "none") || !ft_strcmp(ptr->next->attr, "builtin")))
// 		{
// 			ptr->next->attr = "builtin_sub";
// 			ptr = ptr->next->next;
// 		}
// 		else
// 			ptr = ptr->next;
// 	}
// }

/*
* combine nodes that is not operator or commands
*/
void	combine_nodes(t_node **lst_cmd)
{
	t_node	*ptr;

	ptr = *lst_cmd;
	while (ptr)
	{
		if (!ft_strcmp(ptr->attr, "rdr") && ptr->next
			&& !ft_strcmp(ptr->next->attr, "rdr_sub"))
			ptr = make_rdr_group(ptr);
		else if (!ft_strcmp(ptr->attr, "none") || !ft_strcmp(ptr->attr, "space"))
			ptr = combine_w_prev(ptr);
		else if (!ft_strcmp(ptr->attr, "builtin")
			|| ((!ft_strcmp(ptr->attr, "rdr") || !ft_strcmp(ptr->attr, "pipe"))
				&& ptr->next && ft_strcmp(ptr->next->attr, "none")))
			ptr = combine_w_next(ptr);
		if (ptr && ptr->next)
			ptr = ptr->next;
		else
			break ;
	}
}
		// else if (!ft_strcmp(ptr->attr, "builtin") && ptr->next
		// 	&& !ft_strcmp(ptr->next->attr, "builtin_sub"))
		// 	ptr = make_builtin_grp(ptr);
