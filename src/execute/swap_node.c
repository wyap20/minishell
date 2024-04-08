/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:01:49 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 16:13:29 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*part of ft_sort to swap content of 2 nodes */
void	ft_swap_info(t_node *a, t_node *b)
{
	char	**cmds;
	char	*attr;
	char	*content;
	char	*quote_type;

	cmds = a->cmds;
	a->cmds = b->cmds;
	b->cmds = cmds;
	attr = a->attr;
	a->attr = b->attr;
	b->attr = attr;
	content = a->content;
	a->content = b->content;
	b->content = content;
	quote_type = a->quote_type;
	a->quote_type = b->quote_type;
	b->quote_type = quote_type;
}

/* part of ft_sort to preserve sequence/order once a swap happens*/
void	ft_reorder(t_node *dst, t_node *x)
{
	if (dst == x)
		return ;
	else
	{
		while (dst != x)
		{
			ft_swap_info(dst, x);
			dst = dst->next;
		}
	}
}

/* iterate through nodes that are in correct position */
t_node	*ft_get_req_node(t_node *x)
{
	while (!ft_strcmp(x->attr, "rdr") && x->next != NULL)
		x = x->next;
	return (x);
}

/* swap and reorder the nodes function */
t_node	*ft_swap_reorder(t_node *dst, t_node *x)
{
	ft_swap_info(dst, x);
	dst = dst->next;
	ft_reorder(dst, x);
	return (dst);
}

/* re-arrange commands in each group so that redirections runs 1st */
void	ft_sort(t_node *lst)
{
	t_node	*x;
	t_node	*dst;

	x = lst;
	if (x->next == NULL)
		return ;
	while (x != NULL)
	{
		x = ft_get_req_node(x);
		dst = x;
		while (x != NULL && ft_strcmp(x->attr, "pipe"))
		{
			if (!ft_strcmp(x->attr, "rdr"))
			{
				if (dst->attr != x->attr)
				{
					dst = ft_swap_reorder(dst, x);
				}
			}
			x = x->next;
		}
		if (x != NULL)
			x = x->next;
	}
}
