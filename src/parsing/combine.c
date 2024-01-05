/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:05:50 by wyap              #+#    #+#             */
/*   Updated: 2024/01/05 14:23:08 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*combine nodes between operator and/or commands*/
void	combine_nodes(t_node **lst_cmd)
{
	t_node 	*ptr;
	t_node	*tmp1;
	t_node	*tmp2;
	// char	*addr_left;
	// char	*addr_right;

	ptr = *lst_cmd;
	if (!ft_strcmp(ptr->attr, "operator") || !ft_strcmp(ptr->attr, "builtin"))
		tmp1 = ptr;

}