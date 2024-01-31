/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:05:53 by wyap              #+#    #+#             */
/*   Updated: 2024/01/29 13:25:23 by wyap             ###   ########.fr       */
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
	printf("mark A: minishell -> export: invalid format: %s\n", buf);
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
			// free(add[i]);
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
int	new_arr_size(char **add)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (add[i])
	{
		if (add[i][0] == ' ')
		{
			i++;
			// printf("line %d is blank\n", i);
			j++;
		}
		else
			i++;
	}
	// printf("total var count:%d\n", i);
	// printf("invalid_var count:%d\n",j);
	return (i - j);
}

/*validate eligible new key/value to be added in the environment*/
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
		{
			if (!ft_strchr(add[i], '='))
			{
				free(add[i]);
				add[i] = ft_strdup(" ");
				// printf("line %d set to blank\n", i);
			}
			else
				add[i] = check_remain_char1(add[i]);
		}
		else if (!ft_isalpha(add[i][0])) //if first char is not alpha
			add[i] = check_remain_char2(add[i]);
		i++;
	}
	for (int k = 0; add[k] ; k++)
		printf("%d: %s\n", k, add[k]);
	size = new_arr_size(add);
	updated = valid_vars(add, size);
	return (updated);
}
