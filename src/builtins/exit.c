/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:18 by wyap              #+#    #+#             */
/*   Updated: 2024/02/13 14:02:37 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_env *env, char *cmd_buf)
{
	printf("exit\n");
	if (!cmd_buf)
		free(cmd_buf);
	rl_clear_history();
	free_2d_arr(env->env_vars);
	free_2d_arr(env->paths);
	free(env->env_path);
	free(env->home_tilde);
	exit(0);
}
