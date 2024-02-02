/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:33:43 by atok              #+#    #+#             */
/*   Updated: 2024/01/30 23:11:49 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
* these functions handles syntax errors BEFORE lst_cmd is initiated
*/

void ft_loop_to_pair(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != c && str[*i] != 0x00)
		(*i)++;
	if (str[*i] == c)
		c = 0x00;
	if (str[*i] == 0x00)
	return;	
}

int	ft_check_arrow(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{	
			ft_loop_to_pair(str, &i, str[i]);
		}
		if (str[i] == '<' || str[i] == '>')
			if (str[i + 1] == str[i] && str[i + 2] == str[i])
				return (-1);
		i++;
	}
	return (0);
}

int	ft_check_quote(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = 0x00;
	while (str[i] != 0x00 && c == 0x00)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i] != 0x00)
				i++;
			if (str[i] == c)
				c = 0x00;
			if (str[i] == 0x00)
				break ;
		}
		i++;
	}
	if (c != 0x00)
		return (printf("Error %c quote\n", c), -1);
	return (0);
}

/*check command: reject unclosed quote and more than triple arrow*/
bool	check_cmd(char *cmd_str)
{
	if (!ft_strcmp(cmd_str, "<<") || !ft_strcmp(cmd_str, ">>") || !ft_strcmp(cmd_str, "<") || !ft_strcmp(cmd_str, ">") || !ft_strcmp(cmd_str, "|"))
	{
		printf("minishell: syntax error near unexpected token [check_cmd]\n");
		return (false);
	}
	if (ft_check_quote(cmd_str) == -1)
		return (false);
	if (ft_check_arrow(cmd_str) == -1)
	{
		printf("Arrow Parse Error\n");
		return (false);
	}
	if (cmd_str[0] == 0 && str_not_empty(cmd_str))
		return (false);
	// printf("\t**Quote and arrow OK!**\n");
	return (true);
}
