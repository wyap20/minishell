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

void	check_first_char(char *str)
{
	char	**split;
	char	*buf;
	int		j;

	if (ft_strchr(str, '='))
	{
		split = ft_split(str, '='); //split before first equal sign check if the rest is alphanumeric
		buf = split[0];
	}
	else
		return ;
	if (buf)
	{
		j = 1;
		while (buf[j])
		{
			if (!ft_isalnum(buf[j]) && buf[j] != '_') //if remaining char is not alnum (how to add exception)
				printf("mark B: minishell -> export: invalid format: %s\n", buf);
			j++;
		}
	}
	free_2d_arr(split);
}

void	check_remain_char(char *str)
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
}

void	check_export(char **add)
{
	int	i;

	i = 0;
	while (add[i])
	{
		if (ft_isalpha(add[i][0]) || add[i][0] == '_') //if first char is alpha or underscore
			check_first_char(add[i]);
		else if (!ft_isalpha(add[i][0])) //if first char is not alpha
			check_remain_char(add[i]);
		i++;
	}
}

// void	check_export(char **add)
// {
// 	int		i;
// 	int		j;
// 	char	**split;
// 	char	*buf;
// 	i = 0;
// 	buf = NULL;
// 	while (add[i])
// 	{
// 		if (ft_isalpha(add[i][0]) || add[i][0] == '_') //if first char is alpha or underscore
// 		{
// 			if (ft_strchr(add[i], '='))
// 			{
// 				split = ft_split(add[i], '='); //split before first equal sign check if the rest is alphanumeric
// 				buf = split[0];
// 			}
// 			else
// 				i++;
// 			if (buf)
// 			{
// 				j = 1;
// 				while (buf[j])
// 				{
// 					if (!ft_isalnum(buf[j])) //if remaining char is not alnum (how to add exception)
// 					{
// 						if (buf[j] == '_') //with the exception of underscore
// 							j++;
// 						else
// 							printf("mark B: minishell -> export: invalid format: %s\n", buf);
// 					}
// 					j++;
// 				}
// 			}
// 		}
// 		else if (!ft_isalpha(add[i][0])) //if first char is not alpha
// 		{
// 			if (ft_strchr(add[i], '='))
// 			{
// 				split = ft_split(add[i], '=');
// 				buf = split[0];
// 			}
// 			else
// 				buf = add[i];
// 			printf("mark A: minishell -> export: invalid format: %s\n", buf);
// 		}
// 		buf = NULL;
// 		// printf("%d\n",i);
// 		i++;
// 	}
// 	if (split)
// 	{
// 		j = 0;
// 		while (split[j])
// 			free(split[j++]);
// 		free(split);
// 	}
// }

void	ft_export(t_env *env, char *add)
{
	char	**add_vars;
	// char	**new_vars;
	// int		i;
	// int		j;
	(void) env;

	// i = 0;
	// j = 0;
	add_vars = ft_split(add, ' ');
	check_export(add_vars);
	//check variable name, can only start with alpha
	//check arg format
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
