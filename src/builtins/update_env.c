#include "../../minishell.h"

/*count how many additional strings to malloc*/
int	new_key_count(t_env *env, char **add_vars)
{
	int		i;
	int		j;
	int		count = 0;
	char	**split;
	char	**cur_vars;

	i = 0;
	cur_vars = env->env_vars;
	while (add_vars[i])
	{
		j = 0;
		// printf("%s\n", add_vars[i]);
		split = ft_split(add_vars[i], '=');
		// printf("%s\n", split[0]);
		while (cur_vars[j])
		{
			if (!ft_strncmp(split[0], cur_vars[j], ft_strlen(split[0])))
			{
				printf("mark\n");
				count++;
			}
			j++;
		}
		free_2d_arr(split);
		i++;
	}
	return (get_array_count(add_vars) - count);
}

/*
* malloc new env array size and
* copy env->env_var until before "_" variable
* !!: DIRECT LEAK DETECTED IN WSL (res[i] = ft_strdup(" ");)
*/
char	**copy_env(t_env *env, int size)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc((size + 1) * sizeof(char *)); //+1 ?
	if (!res)
		printf("export: copy_env() malloc failed");
	while (env->env_vars[i] && i < env->key_count - 1)
	{
		res[i] = ft_strdup(env->env_vars[i]);
		i++;
	}
	printf("**copy_env**\ni index:%d\nsize:%d\n*******\n", i ,size);
	while (i <= size)
	{
		res[i] = " ";//ft_strdup(" ");
		i++;
	}
	return (res);
}

/*replacing existing keys with new value*/
char	**update_exist_key(t_env *env, char **res, char **add_vars, int i)
{
	int		j;
	char	*tmp;
	char	**split;

	while (res[i] && i < env->key_count - 1)
	{
		j = 0;
		while (add_vars[j])
		{
			tmp = res[i];
			split = ft_split(add_vars[j], '=');
			if (!ft_strncmp(split[0], res[i], ft_strlen(split[0])))
			{
					// printf("update mark\n");
				res[i] = ft_strdup(add_vars[j]);
					// printf("%d: %s\n", i, res[i]);
				add_vars[j] = ft_strdup(" ");
				free(tmp);
			}
			free_2d_arr(split);
			if (!tmp)
				free(tmp);
			j++;
		}
		i++;
	}
	return (res);
}

/*
* executes after existing keys are updated with new value
* add new key value string into res (2D array)
*/
char	**add_new_key(char **res, char **add_vars, int size, int new_size)
{
	int	i;
	int	j;
	
	i = size - new_size - 1;
		// printf("i:%d\n", i);
	j = 0;
		// for (int k = 0; k < 4; k++)
		// 	printf("%d: %s\n", k, add_vars[k]);
		// printf("adding new key-value\n");
	while (add_vars[j] && i < size)
	{
		if (!ft_strcmp(add_vars[j], " "))
			j++;
		// else
		// {
		res[i] = ft_strdup(add_vars[j]);
			printf("%d: %s added\n", i, res[i]);
		j++;
		i++;
		// }
	}
	return (res);
}

/*
* executes after export variables are checked at check_export()
* copies env->env_var until before "_" variable
* then update existing key with new value
* new key/value pairs are added before "_" variable is copied
* malloc for old env->env_var is freed after update
*/
void	add_to_env(t_env *env, char **add_vars)
{
	char	**res;
	int		new_size; //count of new key
	int		total_size;

	new_size = new_key_count(env, add_vars);
	printf("new_size:%d\n", new_size);
	if (!new_size)
		return ;
	total_size = env->key_count + new_size;
	printf("add_to_env: current env key count: %d\n", env->key_count);
	res = copy_env(env, total_size);
		/*replacing matching keys with new value*/
		printf("add_to_env before update existing key\n");
		// for (int k = 0; k <= total_size; k++)
		// 	printf("%d: %s\n", k, res[k]);
		for (int k = 0; k < 4; k++)
			printf("%d: %s\n", k, add_vars[k]);
	res = update_exist_key(env, res, add_vars, 0);
	printf("add_to_env after update existing key\n");
		for (int k = 0; k < 4; k++)
			printf("%d: %s\n", k, add_vars[k]);
	res = add_new_key(res, add_vars, total_size, new_size);
		// printf("total_size:%d\n", total_size);
	res[total_size - 1] = ft_strdup(env->env_vars[env->key_count - 1]);
	res[total_size] = NULL;
		// printf("after\n");
		// for (int k = 0; k <= total_size; k++)
		// 	printf("%d: %s\n", k, res[k]);
	free_2d_arr(env->env_vars);
	env->env_vars = (char **)malloc((total_size + 1) * sizeof(char *));
	env->env_vars = res;
	env->key_count = total_size + 1;
	printf("add_to_env: updated env key count: %d\n", env->key_count);
}
	// int i = -1;
	// while (res[++i])
	// 	env->env_vars[i] = ft_strdup(res[i]);
	// env->env_vars[i] = NULL;
