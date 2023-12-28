/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:50:06 by wyap              #+#    #+#             */
/*   Updated: 2023/12/28 18:42:56 by wyap             ###   ########.fr       */
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
	env->env_vars = (char **)malloc((i + 1) * sizeof(char *)); //+1 to have additional array for tail node to insert null
	//copy entire env
	i = -1;
	while (envp[++i])
		env->env_vars[i] = ft_substr(envp[i], 0, (ft_strlen(envp[i])));
	env->env_vars[i] = ft_strdup("\0");
}
	// printf("**View stored env**\n");
	// for (int j = 0; env->env_vars[j][0]; j++)
	// 	printf("%d: %s\n", j, env->env_vars[j]);

void	split_path(t_env *env)
{
	if (!env->env_path)
		perror("stored $PATH variable not found/not stored\n");
	env->paths = ft_split(env->env_path, ':');
	//check splitted paths
	// printf("\n**View splitted PATH**\n");
	// for (int i = 0; env->paths[i]; i++)
	// 	printf("%d: %s\n", i, env->paths[i]);
	// printf("\n");
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