#include "../../minishell.h"

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
	while (del[i])
	{
		j = 0;
		while (env->env_vars[j])
		{
			if (del[i] && !ft_strncmp(del[i], env->env_vars[j], ft_strlen(del[i])))
			{
				tmp = env->env_vars[j];
				env->env_vars[j] = ft_strdup(" ");
				free(tmp);
				count++;
			}
			// printf("check del mark\ni:%d\n", i);
			j++;
		}
		i++;
	}
	return (count);
}

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
			printf("replacing %s to blank\n", del[i]);
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

// int	check_del(t_env *env, char **del)
// {
// 	char	*tmp;
// 	int		i;
// 	int		j;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while (del[i])
// 	{
// 		if (!ft_strcmp(del[i], "_") && del[i + 1])
// 			i++;
// 		if (ft_strchr(del[i], '='))
// 		{
// 			tmp = del[i];
// 			del[i] = ft_strdup(" ");
// 			free(tmp);
// 			if (del[i + 1])
// 			i++;
// 		}
// 		j = 0;
// 		while (env->env_vars[j])
// 		{
// 			if (del[i] && !ft_strncmp(del[i], env->env_vars[j], ft_strlen(del[i])))
// 			{
// 				tmp = env->env_vars[j];
// 				env->env_vars[j] = ft_strdup(" ");
// 				free(tmp);
// 				count++;
// 			}
// 			// printf("check del mark\ni:%d\n", i);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

char	**copy_unset_env(t_env *env, int count)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char **)malloc((count + 1) * sizeof(char *)); //+1 ?
	if (!res)
		printf("unset: copy_env() malloc failed");
	while (env->env_vars[i] && i < env->key_count)
	{
		if (!ft_strcmp(env->env_vars[i], " ")) //skip if match
			i++;
		else if (ft_strcmp(env->env_vars[i], " "))
		{
			res[j] = ft_strdup(env->env_vars[i]);
			// printf("%d: %s\n", j, res[j]);
			i++;
			j++;
		}
	}
	// printf("i index:%d\nenv->key_count:%d\n", i ,env->key_count);
	// printf("res size:%i\n\n**copy_unset_env**\n", count);
	// printf("j:%d\n",j);
	res[j] = NULL;
		// for (int k = 0; k < count; k++)
		// 	printf("%d: %s\n", k, res[k]);
	env->key_count = count;
	return (res);
}

void	ft_unset(t_env *env, char **cmds)
{
	char	**res;
	int		count;

	count = 0;
	printf("ft_unset: current env key count: %d\n", env->key_count);
	for (int k = 0; cmds[k]; k++)
		printf("%d: %s\n", k, cmds[k]);
	check_del(cmds);
	for (int k = 0; cmds[k]; k++)
		printf("%d: %s\n", k, cmds[k]);
	count = get_valid_count(env, cmds);
	printf("unset count:%d\n", count);
	if (!count)
		return ;
	res = copy_unset_env(env, env->key_count - count);
	printf("ft_unset: updated env key count: %d\n", env->key_count);
	free_2d_arr(env->env_vars);
	env->env_vars = res;
}

// void	ft_unset(t_env *env, char **cmds)
// {
// 	char	**del_vars;
// 	char	**res;
// 	int		count;

// 	count = 0;
// 	del_vars = cmds;
// 	for (int k = 0; del_vars[k]; k++)
// 		printf("%d: %s\n", k, del_vars[k]);

// 	printf("ft_unset: current env key count: %d\n", env->key_count);
// 	count = check_del(env, del_vars);
// 	for (int k = 0; del_vars[k]; k++)
// 		printf("%d: %s\n", k, del_vars[k]);
// 	printf("unset count:%d\n", count);
// 	if (!count)
// 		return ;
// 	res = copy_unset_env(env, env->key_count - count);
// 	printf("ft_unset: updated env key count: %d\n", env->key_count);
// 	// for (int k = 0; k <= env->key_count; k++)
// 	// 	printf("%d: %s\n", k, res[k]);

// 		// free the unchanged env->env_vars (env->key_count - count) that will replace by res**
// 		// int i = 0;
// 		// while (env->env_vars[i] && i < env->key_count - count + 1)
// 		// {
// 		// 	free(env->env_vars[i]);
// 		// 	i++;
// 		// }
// 	free_2d_arr(env->env_vars);
// 	env->env_vars = res;
// }
