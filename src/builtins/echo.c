/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:04:11 by wyap              #+#    #+#             */
/*   Updated: 2024/02/15 15:01:22 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	check_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || !ft_strcmp(str, "-"))
		return (false);
	while (str[i])
		if (str[i++] != 'n')
			return (false);
	return (true);
}

void	echo_print(char **cmds)
{
	int		i;
	int		j;
	bool	flag;

	flag = false;
	i = 1;
	if (cmds[1])
	{
		flag = check_flag(cmds[1]);
		if (flag == true)
			i = 2;
	}
	while (cmds && cmds[i])
	{
		j = 0;
		while (cmds[i][j])
			printf("%c", cmds[i][j++]);
		if (cmds[i + 1])
			printf(" ");
		i++;
	}
	if (flag == false)
		printf("\n");
}
	// if (!cmds[i])
	// 	return ;
	// printf("%d, %d\n", i, flag);
