/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:32:28 by wyap              #+#    #+#             */
/*   Updated: 2023/12/01 02:14:37 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
node struct:
int index
char *data //parsed string
char *quote {none, s_quote, d_quote}
char *attr {normal, env_var, operator}
prev
next
*/
t_node	*ft_ldlstnew(char *data)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->content = data;
	new->index = -1;
	new->quote_type = "none"; //test if can set as NULL
	new->attr = "none";
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

// t_node	*ft_ldlstnew(long num)
// {
// 	t_node	*new;

// 	new = (t_node *)malloc(sizeof(t_node));
// 	if (!new)
// 		return (NULL);
// 	new->content = num;
// 	new->prev = NULL;
// 	new->next = NULL;
// 	return (new);
// }

void	ft_dlstadd_front(t_node **lst, t_node *new)
{
	if (new == NULL)
		return ;
	if (lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->prev = NULL;
	new->next = *lst;
	if (ft_dlstsize(*lst) >= 1)
		(*lst)->prev = new;
	*lst = new;
}

void	ft_dlstadd_back(t_node **lst, t_node *new)
{
	t_node	*ptr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
	new->next = NULL;
}

int	ft_dlstsize(t_node	*lst)
{
	int		size;
	t_node	*ptr;	

	size = 0;
	if (!lst)
		return (0);
	ptr = lst;
	while (ptr != NULL)
	{
		size++;
		ptr = ptr->next;
	}
	return (size);
}

t_node	*ft_dlstlast(t_node *lst)
{
	t_node	*ptr;

	if (!lst)
		return (0);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
