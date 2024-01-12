/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:31:01 by wyap              #+#    #+#             */
/*   Updated: 2024/01/09 19:54:28 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*
* validate remaining characters of variable to be alphanumeric or underscore
* if no '=', or remaining characters invalid, return space
* otherwise return str as it is
*/
char	*check_remain_char1(char *str)
{
	char	**split;
	char	*buf;
	int		j;

	if (!ft_strchr(str, '='))
		return (" ");
	split = ft_split(str, '='); //split before first equal sign check if the rest is alphanumeric
	buf = split[0];
	if (buf)
	{
		j = 1;
		while (buf[j])
		{
			if (!ft_isalnum(buf[j]) && buf[j] != '_') //if remaining char is not alnum or underscore
			{
				printf("mark B: minishell -> export: invalid format: %s\n", buf);
				return (" ");
			}
			j++;
		}
	}
	free_2d_arr(split);
	return (str);
}

/*
* obtain variable name to be included in error message
* set the string to one space, to be ignored later
*/
char	*check_remain_char2(char *str)
{
	char	**split;
	char	*buf;

	if (ft_strchr(str, '='))
	{
		split = ft_split(str, '=');
		buf = split[0];
	}
	else
		buf = str;
	printf("mark A: minishell -> export: invalid format: %s\n", buf);
	free_2d_arr(split);
	return (" ");
}

/*returns a 2d array containing valid variable to update*/
char **valid_vars(char **add, int size)
{
	char	**updated;
	int		i;
	int		j;

	i = 0;
	j = 0;
	updated = (char **)malloc((size + 1) * sizeof(char *));
	if (!updated)
		printf("export error: failed to update valid variables\n");
	while (add[i])
	{
		if (ft_strcmp(add[i], " "))
		{
			updated[j] = ft_strdup(add[i]);
			free(add[i]);
			j++;
		}
		i++;
	}
	updated[j] = NULL;

	return (updated);
}

int	new_arr_size(char **add)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (add[i])
	{
		if (add[i][0] == ' ')
		{
			i++;
			j++;
		}
		i++;
	}
	printf("i:%d\nj: %d\n", i,j);
	return (i - j);
}

char **check_export(char **add)
{
	char	**updated;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (add[i])
	{
		if (ft_isalpha(add[i][0]) || add[i][0] == '_') //if first char is alpha or underscore
			add[i] = check_remain_char1(add[i]);
		else if (!ft_isalpha(add[i][0])) //if first char is not alpha
			add[i] = check_remain_char2(add[i]);
		i++;
	}
	// printf("export: after checking\n");
	// i = 0;
	// while (add[i])
	// {
	// 	printf("%d: %s\n", i, add[i]);
	// 	i++;
	// }
	size = new_arr_size(add);
	// printf("new arr size:%d\n", size);
	updated = valid_vars(add, size);
	free(add);
	// printf("export: updated\n");
	// while(updated[i])
	// 	printf("%s\n", updated[i++]);
	return (updated);
}

int	get_array_count(char **array)
{
	int	size;
	size = 0;
	while (array[size])
		size++;
	return (size);
}

/*count how many additional arrays to malloc*/
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
malloc new env array size and
copy environmental variable up to before "_" variable
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
	printf("i index:%d\nsize:%d\n", i ,size);
	while (i <= size)
	{
		res[i] = ft_strdup(" ");
		i++;
	}
	return (res);
}

/*replacing matching keys with new value
CANT REPLACE MULTIPLE existing key so far
*/
char	**update_exist_key(t_env *env, char **res, char **add_vars, int i)
{
	int		j;
	char	*tmp;
	char	**split;

	while (res[i]/*[0]*/ && i < env->key_count - 1)
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
		{	
			// printf("hit\n");
			j++;
		}
		// else
		// {
		res[i] = ft_strdup(add_vars[j]);
		// printf("%d: %s\n", i, res[i]);
		j++;
		i++;
		// }
	}
	return (res);
}

/*for each string in add_vars
-compare key in env
	first run -if not match, update 2d array
	-if match, update string
*/
void	add_to_env(t_env *env, char **add_vars)
{
	char	**res;
	int		new_size = 0; //count of new key
	int		total_size;
	new_size = new_key_count(env, add_vars);
	printf("new_size:%d\n", new_size);
	total_size = env->key_count + new_size;
	res = copy_env(env, total_size);

	/*replacing matching keys with new value*/
	// printf("before\n");
	// for (int k = 0; k <= total_size; k++)
	// 	printf("%d: %s\n", k, res[k]);
	// for (int k = 0; k < 4; k++)
	// 	printf("%d: %s\n", k, add_vars[k]);
	res = update_exist_key(env, res, add_vars, 0);
	res = add_new_key(res, add_vars, total_size, new_size);
	// printf("total_size:%d\n", total_size);
	res[total_size - 1] = ft_strdup(env->env_vars[env->key_count - 1]);
	res[total_size] = NULL;

	printf("after\n");
	for (int k = 0; k <= total_size; k++)
		printf("%d: %s\n", k, res[k]);
	// free_2d_arr(add_vars);
	free_2d_arr(env->env_vars);
	env->env_vars = (char **)malloc((total_size + 1) * sizeof(char *));
	env->env_vars = res;
	// printf("%s\n", env->env_vars[33]);
}
	// int i = -1;
	// while (res[++i])
	// 	env->env_vars[i] = ft_strdup(res[i]);
	// env->env_vars[i] = NULL;

void	ft_export(t_env *env, char *add)
{
	char	**add_vars;
	add_vars = ft_split(add, ' ');
	add_vars = check_export(add_vars);
	add_to_env(env, add_vars);
	free_2d_arr(add_vars);
}
