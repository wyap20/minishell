/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:31:01 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 14:44:10 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*updates env->env_path & env->paths after each export*/
void	renew_path(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (env->env_path)
	{
		tmp = env->env_path;
		store_path(env);
		free(tmp);
	}
	else
		store_path(env);
}

/*
* minishell export command
* updates env->env_var with valid key/value pairs
* char *add contains key/value pairs to be checked and update into env->env_var
*/
void	ft_export(t_env *env, char **cmds, char type)
{
	char	**add_vars;
	char	**updated;

	add_vars = cmds;
	updated = check_export(add_vars, env, type);
	add_to_env(env, updated);
	renew_path(env);
	free_2d_arr(updated);
}
	// printf("entered ft_export\n");

	// for (int k = 0; add_vars[k] ; k++)
	// 	printf("%d: %s\n", k, add_vars[k]);

	// printf("export: err_num:%d\n", env->err_num);
	// printf("exited ft_export\n");
