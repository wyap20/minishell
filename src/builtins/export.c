/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:31:01 by wyap              #+#    #+#             */
/*   Updated: 2024/01/29 13:25:43 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
* minishell export command
* updates env->env_var with valid key/value pairs
* char *add contains key/value pairs to be checked and update into env->env_var
*/
void	ft_export(t_env *env, char **cmds)
{
	char	**add_vars;
	char	**updated;

	printf("entered ft_export\n");
	add_vars = cmds;
	for (int k = 0; add_vars[k] ; k++)
		printf("%d: %s\n", k, add_vars[k]);
	updated = check_export(add_vars); //in check_export.c
	// free_2d_arr(add_vars);
	add_to_env(env, updated); //in update_env.c
	free_2d_arr(updated);
	// print_sys_env(env);
	printf("exited ft_export\n");
}

/*
* minishell export command
* updates env->env_var with valid key/value pairs
* char *add contains key/value pairs to be checked and update into env->env_var
*/
// void	ft_export(t_env *env, char *add)
// {
// 	char	**add_vars;
// 	char	**updated;

// 	printf("entered ft_export\n");
// 	add_vars = ft_split(add, ' ');
// 	for (int k = 0; add_vars[k] ; k++)
// 		printf("%d: %s\n", k, add_vars[k]);

// 	updated = check_export(add_vars); //in check_export.c
// 	free_2d_arr(add_vars);
// 	add_to_env(env, updated); //in update_env.c

// 	// 	printf("after\n");
// 	// for (int k = 0; env->env_vars[k]; k++)
// 	// 	printf("%d: %s\n", k, env->env_vars[k]);

// 	free_2d_arr(updated);
// 	printf("exited ft_export\n");
// }
