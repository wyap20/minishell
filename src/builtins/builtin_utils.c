/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:45:23 by wyap              #+#    #+#             */
/*   Updated: 2024/01/04 13:30:15 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_sys_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return ;
}

/*prints out specified environment variable, s* is case sensitive*/
void	print_env_var(char **envp, char *s)
{
	int		i;
	char	**pwd;

	i = -1;
	pwd = NULL;
	s = ft_strjoin(s, "=");
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], s, 4))
		{
			pwd = ft_split(envp[i], '=');
			break ;
		}
	}
	printf("%s\n", pwd[1]);
}
