#include "../../minishell.h"

/*
* check key name against key in env->env_var
* returns an updated list
* ! NOT WORKING IF ALL VARIABLE NOT EXIST IN env_var
*/
int	check_del(t_env *env, char **del)
{
	char	*tmp;
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (del[i])
	{
		if (!ft_strcmp(del[i], "_"))
			i++;
		if (ft_strchr(del[i], '='))
			i++;
		j = 0;
		while (env->env_vars[j])
		{
			if (del[i] && !ft_strncmp(del[i], env->env_vars[j], ft_strlen(del[i])))
			{
				tmp = env->env_vars[j];
				env->env_vars[j] = ft_strdup(" ");
				free(tmp);
				// env->env_vars[j] = " ";
				count++;
				// j++;
			}
			// printf("check del mark\ni:%d\n", i);
			j++;
		}
		i++;
	}
	return (count);
}

char	**copy_unset_env(t_env *env, int count)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char **)malloc((count + 1) * sizeof(char *)); //+1 ?
	if (!res)
		printf("export: copy_env() malloc failed");
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

void	ft_unset(t_env *env, char *del)
{
	char	**del_vars;
	char	**res;
	int		count;

	count = 0;
	del_vars = ft_split(del, ' ');
	for (int k = 0; del_vars[k]; k++)
		printf("%d: %s\n", k, del_vars[k]);

	printf("ft_unset: current env key count: %d\n", env->key_count);
	count = check_del(env, del_vars);
	printf("unset count:%d\n", count);
	free_2d_arr(del_vars);
	// print_sys_env(env);
	if (!count)
		return ;
	res = copy_unset_env(env, env->key_count - count);
	printf("ft_unset: updated env key count: %d\n", env->key_count);
	// res[env->key_count] = NULL;
	// print_sys_env(env);
	// free_2d_arr(env->env_vars);
	for (int k = 0; k <= env->key_count; k++)
		printf("%d: %s\n", k, res[k]);

		// free the unchanged env->env_vars (env->key_count - count) that will replace by res**
		// int i = 0;
		// while (env->env_vars[i] && i < env->key_count - count + 1)
		// {
		// 	free(env->env_vars[i]);
		// 	i++;
		// }

	// env->env_vars = (char **)malloc((env->key_count) * sizeof(char *));
	free_2d_arr(env->env_vars);
	env->env_vars = res;
}