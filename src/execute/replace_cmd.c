/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_cmdv2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:38:57 by atok              #+#    #+#             */
/*   Updated: 2024/02/20 18:08:19 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_cmd_path(char **path, char *cmd)
{
	char	*a;
	char	*b;
	int		i;

	i = 0;
	if (!path)
		return (ft_strdup(cmd));
	a = ft_strjoin("/", cmd);
	while (path[i] != 0x00)
	{
		b = ft_strjoin(path[i], a);
		if (access(b, F_OK) == 0)
		{
			free(a);
			return (b);
		}
		else
			free(b);
		i++;
	}
	free(a);
	return (ft_strdup(cmd));
}

void	set_builtin_attr(t_node *ptr)
{
	if (!ft_strcmp(ptr->cmds[0], "echo") || !ft_strcmp(ptr->cmds[0], "cd")
		|| !ft_strcmp(ptr->cmds[0], "pwd") || !ft_strcmp(ptr->cmds[0], "export")
		|| !ft_strcmp(ptr->cmds[0], "unset") || !ft_strcmp(ptr->cmds[0], "env"))
		ptr->attr = "builtin";
}

/* Function to process each node in the command list*/
void	process_node(t_env *env, t_node *node)
{
	char	*tmp;

	tmp = NULL;
	node->cmds = ft_split_cmds(node->content);
	if (!node->cmds[0])
		return ;
	if (!ft_strcmp(node->cmds[0], "<<"))
	{
		tmp = node->cmds[1];
		node->cmds[1] = get_multiline(node->cmds[1]);
		free(tmp);
	}
	tmp = node->cmds[0];
	set_builtin_attr(node);
	if (ft_strcmp(node->attr, "builtin"))
	{
		node->cmds[0] = ft_get_cmd_path(env->paths, node->cmds[0]);
		free(tmp);
	}
}

/* Function to process the command group list*/
int	process_cmd_group(t_env *env, t_node *lst_cmd)
{
	t_node	*ptr;

	ptr = lst_cmd;
	while (ptr)
	{
		if (g_hdflag == 1)
			return (printf("\n"), 1);
		process_node(env, ptr);
		ptr = ptr->next;
	}
	if (g_hdflag == 1)
		return (printf("\n"), 1);
	else
		return (0);
}

int	create_cmd_group(t_env *env, t_node *lst_cmd)
{
	int	result;

	result = process_cmd_group(env, lst_cmd);
	if (result == 1)
	{
		env->err_num = 130;
		return (1);
	}
	else
		return (0);
}

/* old pre-refactor */
// int	create_cmd_group(t_env *env, t_node *lst_cmd)
// {
// 	t_node	*ptr;
// 	char	*tmp;

// 	ptr = lst_cmd;
// 	while (ptr)
// 	{
// 		if (g_hdflag == 1)
// 			return (printf ("\n"),1);
// 		tmp = NULL;
// 		ptr->cmds = ft_split(ptr->content, ' ');
// 		if (!ptr->cmds[0])
// 			return (0);
// 		if (!ft_strcmp(ptr->cmds[0], "<<"))
// 		{
// 			tmp = ptr->cmds[1];
// 			ptr->cmds[1] = get_multiline(ptr->cmds[1]);
// 			free(tmp);
// 		}
// 		tmp = ptr->cmds[0];
// 		set_builtin_attr(ptr);
// 		if (ft_strcmp(ptr->attr, "builtin"))
// 		{
// 			ptr->cmds[0] = ft_get_cmd_path(env->paths, ptr->cmds[0]);
// 			free(tmp);
// 		}
// 		ptr = ptr->next;
// 	}
// 	if (g_hdflag == 1)
// 		return (printf ("\n"),1);
// 	else
// 		return (0);
// }
