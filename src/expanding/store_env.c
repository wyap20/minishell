/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:50:06 by wyap              #+#    #+#             */
/*   Updated: 2024/02/13 20:57:41 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	store_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	env->env_vars = (char **)malloc((i + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
		env->env_vars[i] = ft_substr(envp[i], 0, (ft_strlen(envp[i])));
	env->env_vars[i] = NULL;
	env->key_count = i;
}
	// printf("**View stored env**\n");
	// for (int j = 0; env->env_vars[j][0]; j++)
	// 	printf("%d: %s\n", j, env->env_vars[j]);

void	split_path(t_env *env)
{
	char	**tmp;

	tmp = NULL;
	if (!env->env_path)
		perror("stored $PATH variable not found/not stored\n");
	if (env->paths)
	{
		tmp = env->paths;
		env->paths = ft_split(env->env_path, ':');
		free_2d_arr(tmp);
	}
	else
		env->paths = ft_split(env->env_path, ':');
}
	//check splitted paths
	// printf("\n**View splitted PATH**\n");
	// for (int i = 0; env->paths[i]; i++)
	// 	printf("%d: %s\n", i, env->paths[i]);
	// printf("\n");

/*store $PATH variable*/
void	store_path(t_env *env)
{
	int	i;

	i = -1;
	while (env->env_vars[++i])
	{
		if (!ft_strncmp(env->env_vars[i], "PATH=", 5))
			env->env_path = ft_substr(env->env_vars[i], 5,
					(int)ft_strlen(env->env_vars[i]) - 5);
	}
	split_path(env);
}

void	store_tilde(t_env *env)
{
	int	i;

	i = -1;
	while (env->env_vars[++i])
	{
		if (!ft_strncmp(env->env_vars[i], "HOME=", 5))
			env->home_tilde = ft_substr(env->env_vars[i],
					5, (int)ft_strlen(env->env_vars[i]) - 5);
	}
}
	// printf("tilde: %s\n", env->home_tilde);
