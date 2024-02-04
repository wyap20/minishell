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

/*skip quoted string*/
void	ft_loop_to_pair(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != c && str[*i] != 0x00)
		(*i)++;
	if (str[*i] == c)
		c = 0x00;
	if (str[*i] == 0x00)
		return ;
}
/*
* check if more than two same arrow
* return true/false for valid/invalid syntax
*/
bool	ft_check_arrow(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '\'' || str[i] == '\"')
			ft_loop_to_pair(str, &i, str[i]);
		if (str[i] == '<' || str[i] == '>')
			if (str[i + 1] == str[i] && str[i + 2] == str[i])
				return (false);
		i++;
	}
	return (true);
}
/*
* check for unclosed quotes
* return 0/-1 if no/contains unclosed quotes
*/
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
		return (printf("minishell: syntax error: unclosed %c quote\n", c), -1);
	return (0);
}

/*
* check command syntax
* error handle:
* standalone rdr w/out space (err_num:2);
* more than double arrow (err_num:2);
* unclosed quotes (err_num:42) [custom value]
* return true/false for valid/invalid syntax
*/
bool	check_cmd(t_env *env, char *cmd_str)
{
	if (ft_check_quote(cmd_str) == -1)
	{
		env->err_num = 42;
		return (false);
	}
	if (!ft_strcmp(cmd_str, "<<") || !ft_strcmp(cmd_str, ">>")
		|| !ft_strcmp(cmd_str, "<") || !ft_strcmp(cmd_str, ">")
		|| !ft_strcmp(cmd_str, "|") || ft_check_arrow(cmd_str) == false)
	{
		printf("minishell: syntax error near unexpected token\n");
		env->err_num = 2;
		return (false);
	}
	if (cmd_str[0] == 0 && str_not_empty(cmd_str))
	{
		env->err_num = 0;
		return (false);
	}
	return (true);
}
//err_num = 42: [undefined bcs not project requirement] custom value
