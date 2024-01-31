/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:04:11 by wyap              #+#    #+#             */
/*   Updated: 2023/12/27 18:05:01 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	echo_print(const char *str)
// {
// 	int		i;
// 	bool	flag;

// 	flag = false;
// 	i = 4;
// 	if (!ft_strncmp(str, "echo -n ", 8))
// 	{
// 		flag = true;
// 		i = 7;
// 	}
// 	// printf("%d, %d\n", i, flag);
// 	while (str[++i])
// 		printf("%c", str[i]);
// 	if (flag == false)
// 		printf("\n");
// }

void	echo_print(const char **cmds)
{
	int		i;
	bool	flag;

	flag = false;
	i = 0;
	if (!ft_strcmp(cmds[1], "-n"))
		flag = true;
	// printf("%d, %d\n", i, flag);
	while (cmds[2][i])
	{
		printf("%c", cmds[2][i]);
		i++;
	}
	if (flag == false)
		printf("\n");
}

/*when implementing node as input
i = 0;
if (!ft_strncmp(node->data, "-n ", 3))
*/