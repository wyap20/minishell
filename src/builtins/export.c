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
	printf("%d\n", size);
	updated = valid_vars(add, size);
	free(add);
	i = 0;
	// printf("export: updated\n");
	// while(updated[i])
	// 	printf("%s\n", updated[i++]);
	return (updated);
}

// char **check_export(char **add)
// {
// 	char	**updated;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	printf("export: before checking\n");
// 	while (add[i])
// 		printf("%s\n", add[i++]);
// 	i = 0;
// 	while (add[i])
// 	{
// 		if (ft_isalpha(add[i][0]) || add[i][0] == '_') //if first char is alpha or underscore
// 			add[i] = check_remain_char1(add[i]);
// 		else if (!ft_isalpha(add[i][0])) //if first char is not alpha
// 			add[i] = check_remain_char2(add[i]);
// 		i++;
// 	}
// 	printf("export: after checking\n");
// 	i = 0;
// 	while (add[i])
//  {
// 		printf("%d: %s\n", i, add[i]);
//      i++;
//  }
// 	i = 0;
// 	while (add[i])
// 	{
// 		if (add[i][0] == ' ')
// 		{
// 			i++;
// 			j++;
// 		}
// 		i++;
// 	}
// 	printf("i:%d\nj: %d\n", i,j);
// 	updated = (char **)malloc((i - j + 1) * sizeof(char *));
// 	if (!updated)
// 		printf("export error: failed to update valid variables\n");
// 	i = 0; j = 0;
// 	printf("export: start update\n");
// 	while (add[i])
// 	{
// 		if (ft_strcmp(add[i], " "))
// 		{
// 			// printf("mark\n");
// 			updated[j] = ft_strdup(add[i]);
// 			free(add[i]);
// 			// printf("updated[%d]: %s\n", j, updated[j]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	updated[j] = NULL;
// 	i = 0;
// 	printf("export: updated\n");
// 	while(updated[i])
// 		printf("%s\n", updated[i++]);
// 	free(add);
// 	return (updated);
// }

void	ft_export(t_env *env, char *add)
{
	char	**add_vars;
	// char	**old_vars;
	// int		i;
	// int		j;
	(void) env;

	// i = 0;
	// j = 0;
	add_vars = ft_split(add, ' ');
	add_vars = check_export(add_vars);
	// while (add_vars[i])
	// 	i++;
	// printf("%d\n", i);
	// while (env->env_vars[j])
	// 	j++;
	// j += i;
	// new_vars = (char **)malloc(j * sizeof(char *));
	// if (!new_vars)
	// 	perror("export error: memory not allocated");
	// i = 0;
	// while (i < j)
	// {
	// 	new_vars[i] = ft_strdup(env->env_vars[i]);
	// 	i++;
	// }
	// j = 0;
	// while (new_vars[i])
	// {
	// 	new_vars[i] = ft_strdup(add_vars[j]);
	// 	i++;
	// 	j++;
	// }

}
