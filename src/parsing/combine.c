/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:05:50 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 16:54:58 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*combine characters that should be redirection*/
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

/*merge current node with previous node*/
t_node	*combine_w_prev(t_node *ptr)
{
	t_node	*tmp;
	char	*content_ptr;

	if (ptr->prev && (!ft_strcmp(ptr->prev->attr, "non")
			|| !ft_strcmp(ptr->prev->attr, "sp")))
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
	if (tmp && (!ft_strcmp(tmp->attr, "non")
			|| !ft_strcmp(tmp->attr, "sp")))
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

void	set_rdr_nodes(t_node *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->attr, "rdr") && lst->next
			&& lst->next->next && !ft_strcmp(lst->next->attr, "sp")
			&& !ft_strcmp(lst->next->next->attr, "non"))
		{
			lst->next->attr = "rdr_sub";
			lst->next->next->attr = "rdr_sub";
			lst = lst->next->next->next;
		}
		else if ((!ft_strcmp(lst->attr, "rdr")
				&& lst->next && !ft_strcmp(lst->next->attr, "non")))
		{
			lst->next->attr = "rdr_sub";
			lst = lst->next->next;
		}
		else
			lst = lst->next;
		if (lst && !ft_strcmp(lst->attr, "sp")
			&& !ft_strcmp(lst->prev->attr, "rdr_sub"))
		{
			lst->attr = "rdr_sub";
			lst = lst->next;
		}
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
		if (!ft_strcmp(ptr->attr, "rdr") && ptr->next
			&& !ft_strcmp(ptr->next->attr, "rdr_sub"))
			ptr = make_rdr_group(ptr);
		else if (!ft_strcmp(ptr->attr, "non") || !ft_strcmp(ptr->attr, "sp"))
			ptr = combine_w_prev(ptr);
		else if (!ft_strcmp(ptr->attr, "builtin")
			|| ((!ft_strcmp(ptr->attr, "rdr") || !ft_strcmp(ptr->attr, "pipe"))
				&& ptr->next && ft_strcmp(ptr->next->attr, "non")))
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
