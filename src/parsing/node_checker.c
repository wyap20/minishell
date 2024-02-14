/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:34:54 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 16:40:02 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
* these functions handles syntax errors that are not captured
* AFTER lst_cmd is initiated and node attr is assigned
*/

/*
* error handle invalid pipe-rdr combination syntax
* return true/false for valid/invalid syntax
*/
bool	check_operator_syntax(t_env *env, t_node *ptr)
{
	if (!ft_strcmp(ptr->content, "<<") || !ft_strcmp(ptr->content, "<")
		|| !ft_strcmp(ptr->content, ">>"))
	{
		if (!ft_strcmp(ptr->next->attr, "pipe")
			|| (!ft_strcmp(ptr->next->attr, "sp")
				&& !ft_strcmp(ptr->next->next->attr, "pipe")))
		{
			printf("minishell: syntax error: near unexpected token\n");
			env->err_num = 2;
			return (false);
		}
	}
	if (!ft_strcmp(ptr->attr, "rdr") && (!ft_strcmp(ptr->next->attr, "rdr")
			|| (!ft_strcmp(ptr->next->attr, "sp")
				&& !ft_strcmp(ptr->next->next->attr, "rdr"))))
	{
		printf("minishell: syntax error near unexpected token\n");
		env->err_num = 2;
		return (false);
	}
	return (true);
}
// if (!ft_strcmp(ptr->attr, "pipe"))
// 	if ((!ft_strcmp(ptr->next->content, ">>")
// 		|| !ft_strcmp(ptr->next->content, ">"))
// 		|| (!ft_strcmp(ptr->next->attr, "sp")
// 		&& (!ft_strcmp(ptr->next->next->content, ">>")
// 		|| !ft_strcmp(ptr->next->next->content, ">"))))
// 		return (false);

/*
* check syntax
* error handle:
* rdr at end of cmd (err_num:2)
* pipe at end of cmd [not project requirement] (err_num:42) [custom]
* return true/false for valid/invalid syntax
*/
bool	check_last_node(t_env *env, t_node *ptr)
{
	printf("entered check last node\n");
	if (!ft_strcmp(ptr->attr, "pipe"))
	{
		printf("minishell: syntax error: pipe at end of cmd\n");
		env->err_num = 42;
		return (false);
	}
	else
	{
		printf("minishell: syntax error near unexpected token\n");
		env->err_num = 2;
		return (false);
	}
	return (true);
}

/*check operator syntax*/
bool	check_operator(t_env *env, t_node **lst_cmd)
{
	t_node	*ptr;

	ptr = *lst_cmd;
	if (!ft_strcmp(ptr->attr, "pipe"))
	{
		printf("minishell: syntax error near unexpected token\n");
		env->err_num = 2;
		return (false);
	}
	if (!ft_strcmp(ft_dlstlast(ptr)->attr, "rdr")
		|| !ft_strcmp(ft_dlstlast(ptr)->attr, "pipe"))
		return (check_last_node(env, ft_dlstlast(ptr)));
	while (ptr)
	{
		if (ptr->next)
			if (check_operator_syntax(env, ptr) == false)
				return (false);
		ptr = ptr->next;
	}
	return (true);
}
