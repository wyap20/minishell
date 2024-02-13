/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:10:17 by wyap              #+#    #+#             */
/*   Updated: 2024/02/13 13:02:00 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_pipe_count(t_exe *exe, t_node **lst_cmd)
{
	t_node	*ptr;

	ptr = *lst_cmd;
	if (!(*lst_cmd))
		return ;
	exe->num_pipes = 0;
	while (ptr)
	{
		if (!ft_strcmp(ptr->attr, "pipe"))
			exe->num_pipes++;
		ptr = ptr->next;
	}
}
	// printf("exe->num_pipes: %d\n", exe->num_pipes);
