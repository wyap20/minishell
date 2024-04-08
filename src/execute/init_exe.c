/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:15:26 by wyap              #+#    #+#             */
/*   Updated: 2024/02/13 16:16:06 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* initialize variable used in execution */
void	ft_initialize_exe_vars(t_exe *exe, t_node **lst)
{
	exe->num_pipes = 0;
	exe->num_cmds = 0;
	get_pipe_count(exe, lst);
	exe->num_cmds = ft_dlstsize(*lst);
	exe->redir[0] = -2;
	exe->redir[1] = -2;
	exe->z = 0;
	exe->pid = malloc((exe->num_pipes + 1) * sizeof(pid_t));
	if (exe->num_pipes > 0)
		exe->pipes = malloc(exe->num_pipes * sizeof(int [2]));
	else if (exe->num_pipes == 0)
		exe->pipes = 0;
}
