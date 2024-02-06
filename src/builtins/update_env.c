#include "../../minishell.h"

/*count how many additional strings to malloc*/
int	new_key_count(t_env *env, char **updated)
{
	int		i;
	int		j;
	int		count;
	char	**split;
	char	**cur_vars;

	i = 0;
	count = 0;
	cur_vars = env->env_vars;
	while (updated[i])
	{
		j = 0;
		printf("%s\n", updated[i]);
		split = ft_split(updated[i], '=');
		printf("%s\n", split[0]);
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
	// printf("update env: get_array_count(updated):%d\n", get_array_count(updated));
	// printf("update env: count:%d\n", count);
	return (get_array_count(updated) - count);
}

/*
* malloc new env array size and
* copy env->env_var until before "_" variable
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
char	**update_exist_key(t_env *env, char **res, char **updated, int i)
{
	int		j;
	char	*tmp;
	char	**split;

	while (res[i] && i < env->key_count - 1)
	{
		j = 0;
		while (updated[j])
		{
			tmp = res[i];
			split = ft_split(updated[j], '=');
			if (!ft_strncmp(split[0], res[i], ft_strlen(split[0])))
			{
					// printf("update mark\n");
				res[i] = ft_strdup(updated[j]);
					printf("%d: %s\n", i, res[i]);
				free(updated[j]);
				updated[j] = ft_strdup(" ");
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
char	**add_new_key(char **res, char **updated, int size, int new_size)
{
	int	i;
	int	j;
	
	i = size - new_size - 1;
		// printf("i:%d\n", i);
	j = 0;
		// for (int k = 0; k < 4; k++)
		// 	printf("%d: %s\n", k, updated[k]);
		printf("\nadding new key-value\n");
	while (updated[j] && i < size)
	{
		if (!ft_strcmp(updated[j], " "))
			j++;
		else if (ft_strcmp(updated[j], " "))
		{
			res[i] = ft_strdup(updated[j]);
				printf("%d: %s added\n", i, res[i]);
			j++;
			i++;
		}
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

void	add_to_env(t_env *env, char **updated)
{
	char	**res;
	int		new_size; //count of new key
	int		total_size;

	new_size = new_key_count(env, updated);
	if (new_size < 0)
		new_size = 0;
	total_size = env->key_count + new_size;
	res = copy_env(env, total_size);
	res = update_exist_key(env, res, updated, 0);
	res = add_new_key(res, updated, total_size, new_size);
	res[total_size - 1] = ft_strdup(env->env_vars[env->key_count - 1]);
	res[total_size] = NULL;
	free_2d_arr(env->env_vars);
	env->env_vars = res;
	env->key_count = total_size;
}
	// int i = -1;
	// while (res[++i])
	// 	env->env_vars[i] = ft_strdup(res[i]);
	// env->env_vars[i] = NULL;

// void	add_to_env(t_env *env, char **updated)
// {
// 	char	**res;
// 	int		new_size; //count of new key
// 	int		total_size;

// 	new_size = new_key_count(env, updated);
// 	printf("add_to_env: new_size:%d\n", new_size);
// 		// if (!new_size) //do not use: will not update existing key if return
// 		// 	return ;
// 	total_size = env->key_count + new_size;
// 	printf("add_to_env: current env key count: %d\n", env->key_count);
// 	res = copy_env(env, total_size);

// 		// /*replacing matching keys with new value*/
// 		// for (int k = 0; k <= total_size; k++)
// 		// 	printf("%d: %s\n", k, res[k]);

// 	// printf("add_to_env before update existing key\n");
// 	// 	for (int k = 0; k < 4; k++)
// 	// 		printf("%d: %s\n", k, updated[k]);
// 	res = update_exist_key(env, res, updated, 0);

// 	// printf("add_to_env after update existing key\n");
// 	// 	for (int k = 0; k < 4; k++)
// 	// 		printf("%d: %s\n", k, updated[k]);
// 	res = add_new_key(res, updated, total_size, new_size);
// 		// printf("total_size:%d\n", total_size);
// 	res[total_size - 1] = ft_strdup(env->env_vars[env->key_count - 1]);
// 	res[total_size] = NULL;

// 		// printf("after\n");
// 		// for (int k = 0; k <= total_size; k++)
// 		// 	printf("%d: %s\n", k, res[k]);

// 	free_2d_arr(env->env_vars);
// 	// env->env_vars = (char **)malloc((total_size + 1) * sizeof(char *));
// 	env->env_vars = res;
// 	env->key_count = total_size;
// 	printf("add_to_env: updated env key count: %d\n", env->key_count);
// }