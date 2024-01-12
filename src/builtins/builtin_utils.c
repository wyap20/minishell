/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:45:23 by wyap              #+#    #+#             */
/*   Updated: 2024/01/04 13:30:15 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*get count of strings in 2D array*/
int	get_array_count(char **array)
{
	int	size;
	size = 0;
	while (array[size])
		size++;
	return (size);
}

/*
* minishell env command
* loops through each string of env_var 2D array
* and prints each string as terminal output
*/
void	print_sys_env(t_env *env)
{
	int	i;

	i = -1;
	while (env->env_vars[++i])
		printf("%s\n", env->env_vars[i]);
	return ;
}

/*
* used by minishell pwd command
* prints out specified environment variable, s* is case sensitive
*/
void	print_env_var(char **envp, char *s)
{
	int		i;
	char	**pwd;

	i = -1;
	pwd = NULL;
	s = ft_strjoin(s, "=");
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], s, 4))
		{
			pwd = ft_split(envp[i], '=');
			break ;
		}
	}
	printf("%s\n", pwd[1]);
}
