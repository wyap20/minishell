/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:31:01 by wyap              #+#    #+#             */
/*   Updated: 2024/01/09 19:54:28 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
* minishell export command
* updates env->env_var with valid key/value pairs
* char *add contains key/value pairs to be checked and update into env->env_var
*/
void	ft_export(t_env *env, char *add)
{
	char	**add_vars;

	add_vars = ft_split(add, ' ');
	add_vars = check_export(add_vars);
	add_to_env(env, add_vars);
	free_2d_arr(add_vars);
}
