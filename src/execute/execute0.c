/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:20:44 by atok              #+#    #+#             */
/*   Updated: 2024/01/27 13:20:44 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* set up the pipes before running/executing commands for each gorup */
void	ft_set_pipe(t_exe *exe, int i)
{
	if (exe->num_pipes == 0)
		return ;
	if (i > 0)
	{
		dup2(exe->pipes[i - 1][0], STDIN_FILENO);
		close(exe->pipes[i - 1][0]);
		close(exe->pipes[i - 1][1]);
	}
	if (i < exe->num_pipes)
	{
		dup2(exe->pipes[i][1], STDOUT_FILENO);
		close(exe->pipes[i][0]);
		close(exe->pipes[i][1]);
	}
}

/* build the number of pipes needed */
void	ft_exe_pipe(t_exe *exe)
{
	int	i;

	i = 0;
	while (i < exe->num_pipes)
	{
		if (pipe(exe->pipes[i]) == -1)
			perror("pipe");
		i++;
	}
}

/* runs all the command for the groups */
void	ft_run_cmds(t_exe *exe, t_node *lst, t_env *env, char type)
{
	while (lst != NULL && lst->cmds[0][0] != '|')
	{
		if ((lst->cmds[0][0] == '<' || lst->cmds[0][0] == '>')
			&& !ft_strcmp(lst->attr, "rdr"))
		{
			ft_redir_left(exe, lst, env);
			ft_redir_right(exe, lst);
		}
		else
		{
			if (!ft_strcmp(lst->attr, "builtin"))
				run_builtin(env, lst, type);
			else
				ft_execute(lst, env);
		}
		lst = lst->next;
	}
}

/* itterates to the next group of commands for the next pid/fork/child to run */
t_node	*ft_get_group(t_node *lst, int i)
{
	if (i != 0)
	{
		while (lst->cmds[0][0] != '|')
		{
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (lst);
}

/* the bread and butter */
void	ft_multi_pipe(t_exe *exe, t_node *lst, t_env *env)
{
	int	i;

	i = 0;
	ft_exe_pipe(exe);
	while (i < exe->num_pipes + 1)
	{
		lst = ft_get_group(lst, i);
		exe->pid[i] = fork();
		if (exe->pid[i] == 0)
		{
			ft_set_pipe(exe, i);
			ft_close_all_pipes(exe);
			ft_run_cmds(exe, lst, env, 'c');
			exit(0);
		}
		i++;
	}
}
