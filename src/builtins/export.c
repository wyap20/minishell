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

void	check_export(char **add)
{
	int		i;
	int		j;
	char	**split;
	char	*buf;
	i = 0;
	j = 0;
	buf = NULL;
	while (add[i])
	{
		if (!add[i])
			break;
		if (!ft_isalpha(add[i][0])) //check first char must be alphabetical char
		{
			if (ft_strchr(add[i], '='))
			{
				split = ft_split(add[i], '=');
				buf = split[0];
			}
			else
				buf = add[i];
			printf("mark A: minishell -> export: invalid format: %s\n", buf);
			i++;
		}
		else if (ft_isalpha(add[i][0])) //if first char ok
		{
			j = 1;
			if (ft_strchr(add[i], '='))
			{
				split = ft_split(add[i], '='); //split before first equal sign check if the rest is alphanumeric
				buf = split[0];
			}
			else
				i++;
			if (buf)
				while (buf[j])
					if (!ft_isalnum(buf[j++]))
						printf("mark B: minishell -> export: invalid format: %s\n", buf);
		}
		buf = NULL;
		i++;
	}
	if (split)
	{
		j = 0;
		while (split[j])
			free(split[j++]);
		free(split);
	}
}

void	ft_export(t_env *env, char *add)
{
	char	**add_vars;
	// char	**new_vars;
	int		i;
	int		j;
	(void) env;

	i = 0;
	j = 0;
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
