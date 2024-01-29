/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:18 by wyap              #+#    #+#             */
/*   Updated: 2024/01/29 16:07:41 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_env *env, char *cmd_buf)
{
	free(cmd_buf); //readline malloc buffer
	rl_clear_history();
	free_2d_arr(env->env_vars);
	free_2d_arr(env->paths);
	free(env->env_path);
	free(env->home_tilda);
	exit(1);
}