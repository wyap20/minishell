#include "../../minishell.h"

/*
* these functions handles syntax errors that are not captured
* AFTER lst_cmd is initiated and node attr is assigned
*/

bool	check_operator_syntax(t_node *ptr)
{
	if (!ft_strcmp(ptr->content, "<<") || !ft_strcmp(ptr->content, "<") || !ft_strcmp(ptr->content, ">>"))
	{
		if (!ft_strcmp(ptr->next->attr, "pipe") || (!ft_strcmp(ptr->next->attr, "space") && !ft_strcmp(ptr->next->next->attr, "pipe")))
		{
			printf("Syntax Error: invalid rdr-pipe syntax\n");//printf("minishell: syntax error near unexpected token\n");
			return (false);
		}
	}
	if (!ft_strcmp(ptr->attr, "rdr") && (!ft_strcmp(ptr->next->attr, "rdr") || (!ft_strcmp(ptr->next->attr, "space") && !ft_strcmp(ptr->next->next->attr, "rdr"))))
	{
		printf("Syntax Error: invalid rdr-pipe syntax\n");//printf("minishell: syntax error near unexpected token\n");
		return (false);
	}
	// if (!ft_strcmp(ptr->attr, "pipe"))
	// 	if ((!ft_strcmp(ptr->next->content, ">>") || !ft_strcmp(ptr->next->content, ">")) || (!ft_strcmp(ptr->next->attr, "space") && (!ft_strcmp(ptr->next->next->content, ">>") || !ft_strcmp(ptr->next->next->content, ">"))))
	// 		return (false);
	return (true);
}

bool	check_only_node(t_node *ptr)
{
	// printf("entered check only node\n");
	if (!ft_strcmp(ptr->attr, "pipe"))// || !ft_strcmp(ptr->attr, "rdr"))
	{
		printf("minishell: syntax error near unexpected token [check node]\n");
		return (false);
	}
	return (true);
}

bool	check_last_node(t_node *ptr)
{
	printf("entered check last node\n");
	if (!ft_strcmp(ptr->attr, "pipe"))
	{
		printf("minishell: syntax error: pipe at end of cmd [not project requirement]\n");
		return (false);
	}
	else
	{
		printf("Syntax Error: rdr at end of cmd\n"); //printf("minishell: syntax error near unexpected token\n");
		return (false);
	}
	return (true);
}

	// printf("lst_size:%d\n", ft_dlstsize(ptr));
bool	check_operator(t_node **lst_cmd)
{
	t_node	*ptr;

	ptr = *lst_cmd;
	if (ft_dlstsize(ptr) == 2) //head node addr is NULL
		return (check_only_node(ptr));
	if (!ft_strcmp(ptr->attr, "pipe"))
	{
		printf("Syntax Error: | at start of cmd\n"); //printf("minishell: syntax error near unexpected token\n");
		return (false);
	}
	if (!ft_strcmp(ft_dlstlast(ptr)->attr, "rdr") || !ft_strcmp(ft_dlstlast(ptr)->attr, "pipe"))
		return (check_last_node(ft_dlstlast(ptr)));
	while (ptr)
	{
		if (ptr->next)
			if (check_operator_syntax(ptr) == false)
				return (false);
		ptr = ptr->next;
	}
	return (true);
}
