/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:05:53 by wyap              #+#    #+#             */
/*   Updated: 2024/02/13 14:00:14 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
* executes when first character is alphabet or underscore
* validate remaining characters of variable to be alphanumeric or underscore
* if no '=', or remaining characters is invalid, free str and return space
* otherwise return str as it is
*/
char	*check_remain_char1(char *str)
{
	char	**split;
	char	*buf;
	int		j;

	split = ft_split(str, '=');
	buf = split[0];
	if (buf)
	{
		j = 1;
		while (buf[j])
		{
			if (!ft_isalnum(buf[j]) && buf[j] != '_')
			{
				printf("minishell: export: '%s':not a valid identifier\n", buf);
				free_2d_arr(split);
				free(str);
				return (ft_strdup(" "));
			}
			j++;
		}
	}
	free_2d_arr(split);
	return (str);
}

/*
* executes when first character of the key is not an alphabet
* obtain variable name to be included in error message
* set the string to one space, to be ignored later
*/
char	*check_remain_char2(char *str)
{
	char	**split;
	char	*buf;

	split = NULL;
	if (ft_strchr(str, '='))
	{
		split = ft_split(str, '=');
		buf = split[0];
	}
	else
		buf = str;
	printf("minishell: export: '%s':not a valid identifier\n", buf);
	free_2d_arr(split);
	free(str);
	return (ft_strdup(" "));
}

/*returns a 2d array containing valid variable to update*/
char	**valid_vars(char **add, int size)
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
			j++;
		}
		i++;
	}
	updated[j] = NULL;
	return (updated);
}

/*
* skips string that has space to get the count of valid key/value pairs
* to malloc the right size in updated 2D array with valid key/value pair
* used in check_export()
*/
int	new_arr_size(char **add, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (add[i])
	{
		if (add[i][0] == ' ')
		{
			if (i != 0)
				env->err_num = 1;
			i++;
			j++;
		}
		else
			i++;
	}
	return (i - j);
}
	// printf("total var count:%d\n", i);
	// printf("invalid_var count:%d\n",j);
	// printf("valid_var count:%d\n", i-j);
	// printf("export: err_num:%d\n", env->err_num);

/*validate eligible new key/value to be added in the environment*/
char	**check_export(char **add, t_env *env)
{
	char	**updated;
	int		i;
	int		size;

	i = 0;
	while (add[i])
	{
		if (ft_isalpha(add[i][0]) || add[i][0] == '_')
		{
			if (!ft_strchr(add[i], '='))
			{
				free(add[i]);
				add[i] = ft_strdup(" ");
			}
			else
				add[i] = check_remain_char1(add[i]);
		}
		else if (!ft_isalpha(add[i][0]))
			add[i] = check_remain_char2(add[i]);
		i++;
	}
	size = new_arr_size(add, env);
	updated = valid_vars(add, size);
	return (updated);
}
	// for (int k = 0; add[k] ; k++)
	// 	printf("%d: %s\n", k, add[k]);
