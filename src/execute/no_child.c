/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:10:18 by wyap              #+#    #+#             */
/*   Updated: 2024/02/13 16:10:51 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


/* exclusively run when no pipe or only 1 cmd group */
void	ft_if_no_pipes(t_exe *exe, t_node *lst, t_env *env)
{
	if (exe->pipes == 0)
	{
		while (lst != NULL)
		{
			if (!ft_strcmp(lst->attr, "builtin"))
			{
				if (!ft_strcmp(lst->cmds[0], "export")
					|| !ft_strcmp(lst->cmds[0], "unset")
					|| !ft_strcmp(lst->cmds[0], "cd"))
					run_builtin(env, lst);
				return ;
			}
			lst = lst->next;
		}
	}
}