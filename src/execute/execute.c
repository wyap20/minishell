/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:09:21 by wyap              #+#    #+#             */
/*   Updated: 2024/02/13 16:21:16 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* waits for all child process to end to get final error number */
void	ft_wait_pid(t_exe *exe, t_env *env)
{
	int	i;
	int	status;

	i = 0;
	while (i < exe->num_pipes + 1)
	{
		if (waitpid(exe->pid[i], &status, 0) > 0)
		{
			if (WIFEXITED(status))
				env->err_num = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				if (WTERMSIG(status) != 0)
					env->err_num = 130;
		}
		i++;
	}
}

/* frees pipes and pid */
void	ft_free_pp(t_exe *exe)
{
	free(exe->pid);
	if (exe->num_pipes > 0)
		free(exe->pipes);
}

void	sig_nl(int sig_num)
{
	if (sig_num != SIGINT)
		return ;
	write(1, "\n", 1);
}

/* execute commands starts here */
void	ft_execute_cmd(t_env *env, t_node **lst)
{
	t_exe	exe;

	ft_initialize_exe_vars(&exe, lst);
	signal(SIGINT, sig_nl);
	ft_multi_pipe(&exe,*lst, env);
	ft_close_all_pipes(&exe);
	ft_wait_pid(&exe, env);
	ft_free_pp(&exe);
	if (exe.num_pipes == 0 && env->err_num == 0)
		ft_if_no_pipes(&exe, *lst, env);
}
