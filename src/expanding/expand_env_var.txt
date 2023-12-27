/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:33:21 by wyap              #+#    #+#             */
/*   Updated: 2023/11/28 20:18:04 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//var cannot start with digits, cannot contain special chars
//after parsing, loop through each node to replace $variable
char *ft_expand_dollar_sign(char *str)
{
	int		i;
	int		j;
	char	*var_name;

	i = 0;
	j = 0;
	printf("entering dollar handler\n");
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '$')
		{
			i++;
			// use substr instead?
			while (str[i] != ' ' && ft_isalnum(str[i]) == 1)
			{
				i++;
				j++;
			}
			i -= j;
			var_name = ft_substr(str, i, j);
			// var_name = 
			// 	var_name[j] = str[i];
			// 	i++;
			// 	j++;
			// var_name[j + 1] = '\0';
			printf("var: %s\n", var_name);
		}
		i++;
	}
	return (var_name);
}

int main()
{
	char *s;
	s = readline("test>");
	ft_expand_dollar_sign(s);
	return (0);
}