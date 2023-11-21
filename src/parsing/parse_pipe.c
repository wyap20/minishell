/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:10:17 by wyap              #+#    #+#             */
/*   Updated: 2023/11/21 17:24:11 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*handle single pipe, reject OR operator*/
int	parse_pipe(char *cmd_str)
{
	printf("entered:\n%s\n", cmd_str);
	int	i;
	int	count;

	i = ft_strlen(cmd_str) - 1;
	count = 0;
	if (cmd_str[0] == '|' || cmd_str[i] == '|') //cmd end with '|'
	{
		perror("cmd start/ended with '|'");
		return (1);
	}
	i = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '|' && cmd_str[i + 1] == '|'){ //reject OR operator, do nothing
			perror(" || detected");
			return(1);
		}
		else if (cmd_str[i] == '|')
			count++;
		i++;
	}
	printf("pipe count: %d\n", count);
	return (count);
}