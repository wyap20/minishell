/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:50:06 by wyap              #+#    #+#             */
/*   Updated: 2023/11/28 18:08:20 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	store_env(t_env *env, char **envp)
{
	// (void) env;
	int	i;

	i = 0;
	while (envp[i])
		i++;
	// printf("%d\n", i);
	env->env_vars = (char **)malloc(i * sizeof(char *));
	//copy entire env
	i = -1;
	while (envp[++i])
		env->env_vars[i] = ft_substr(envp[i], 0, (ft_strlen(envp[i])));
	// check stored env
	// for (i = 0; env->env_vars[i]; i++)
	// 	printf("%s\n", env->env_vars[i]);
}

void	split_path(t_env *env)
{
	if (!env->env_path)
		perror("stored $PATH variable not found/not stored\n");
	env->paths = ft_split(env->env_path, ':');
	//check splitted paths
	// for (int i = 0; env->paths[i]; i++)
	// 	printf("%d: %s\n", i, env->paths[i]);
}

/*store $PATH variable*/
void	store_path(t_env *env, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i]) //find PATH variable in envp
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			env->env_path = ft_substr(envp[i], 5, (int)ft_strlen(envp[i]) - 5);
	}
	split_path(env);
}