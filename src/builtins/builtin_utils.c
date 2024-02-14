/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:45:23 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 16:20:42 by wyap             ###   ########.fr       */
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

/*get HOME in env_vars
* used in ft_cd
*/
char	*get_env_home(t_env *env)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = -1;
	while (env->env_vars[++i])
	{
		if (!ft_strncmp(env->env_vars[i], "HOME=", 5))
			ret = ft_substr(env->env_vars[i], 5,
					(int)ft_strlen(env->env_vars[i]) - 5);
	}
	return (ret);
}

/*
* prints out specified environment variable, s* is case sensitive
*/
// void	print_env_var(char **envp, char *s)
// {
// 	int		i;
// 	char	**sys_var;

// 	i = -1;
// 	sys_var = NULL;
// 	s = ft_strjoin(s, "=");
// 	while (envp[++i])
// 	{
// 		if (!ft_strncmp(envp[i], s, 4))
// 		{
// 			sys_var = ft_split(envp[i], '=');
// 			break ;
// 		}
// 	}
// 	printf("%s\n", sys_var[1]);
// 	free(s);
// 	free_2d_arr(sys_var);
// }
