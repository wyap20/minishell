/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:05:18 by wyap              #+#    #+#             */
/*   Updated: 2024/02/13 15:40:48 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
* free env_path and paths if $PATH is unset
*/
void	if_unset_path(t_env *env, char	*var)
{
	if (var && !ft_strncmp(var, "PATH=", 5))
	{
		free_2d_arr(env->paths);
		free(env->env_path);
		env->paths = NULL;
		env->env_path = NULL;
	}
}
		// printf("unset PATH\n");
		// printf("%s\n", env->env_path);
		// printf("\n**View splitted PATH**\n");
		// for (int i = 0; env->paths[i]; i++)
			// printf("%d: %s\n", i, env->paths[i]);
			// printf("%s\n", env->paths[0]);

/*
* check if any variable in del matches that in current env_var
* returns count of matches;
*/
int	get_valid_count(t_env *env, char **del)
{
	int		i;
	int		j;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	while (del[i++])
	{
		j = 0;
		while (env->env_vars[j])
		{
			if (del[i] && ft_strcmp(env->env_vars[j], " ")
				&& !ft_strncmp(del[i], env->env_vars[j], ft_strlen(del[i])))
			{
				tmp = env->env_vars[j];
				if_unset_path(env, tmp);
				env->env_vars[j] = ft_strdup(" ");
				free(tmp);
				count++;
			}
			j++;
		}
	}
	return (count);
}
	// printf("check del mark\ni:%d\ncount:%d\n", i, count);

/*
* filter invalid arguments cases:
* variable "_" cannot be unset; variable ending with = is invalid
* other invalid arguments are not counted when get_count
* updates list of variables to unset
*/
void	check_del(char **del)
{
	char	*tmp;
	int		i;

	i = 0;
	while (del[i])
	{
		if (ft_strchr(del[i], '=') || !ft_strcmp(del[i], "_"))
		{
			tmp = del[i];
			del[i] = ft_strdup(" ");
			free(tmp);
			if (del[i + 1])
				i++;
		}
		else
			i++;
	}
}
	// printf("replacing %s to blank\n", del[i]);

char	**copy_unset_env(t_env *env, int count)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char **)malloc((count + 1) * sizeof(char *));
	if (!res)
		printf("unset: copy_env() malloc failed");
	while (env->env_vars[i] && i < env->key_count)
	{
		if (!ft_strcmp(env->env_vars[i], " "))
			i++;
		else if (ft_strcmp(env->env_vars[i], " "))
		{
			res[j] = ft_strdup(env->env_vars[i]);
			i++;
			j++;
		}
	}
	res[j] = NULL;
	env->key_count = count;
	return (res);
}
	// printf("i index:%d\nenv->key_count:%d\n", i ,env->key_count);
	// printf("res size:%i\n\n**copy_unset_env**\n", count);
	// printf("j:%d\n",j);
		// for (int k = 0; k < count; k++)
		// 	printf("%d: %s\n", k, res[k]);

void	ft_unset(t_env *env, char **cmds)
{
	char	**res;
	int		count;

	count = 0;
	check_del(cmds);
	count = get_valid_count(env, cmds);
	if (!count)
		return ;
	res = copy_unset_env(env, env->key_count - count);
	free_2d_arr(env->env_vars);
	env->env_vars = res;
}
	// printf("ft_unset: current env key count: %d\n", env->key_count);
	// for (int k = 0; cmds[k]; k++)
	// 	printf("%d: %s\n", k, cmds[k]);
	// printf("unset count:%d\n", count);
	// printf("ft_unset: updated env key count: %d\n", env->key_count);
