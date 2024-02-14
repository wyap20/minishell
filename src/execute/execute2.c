/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:28:55 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 16:32:06 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_cmd_not_found(char *str)
{
	char	*buf;
	char	*tmp;

	buf = ft_strjoin("minishell: ", str);
	tmp = buf;
	buf = ft_strjoin(buf, ":");
	free(tmp);
	tmp = buf;
	buf = ft_strjoin(buf, " command not found\n");
	free(tmp);
	write(2, buf, ft_strlen(buf));
	free(buf);
}

void	ft_print_no_file_or_dir(char *str)
{
	char	*buf;
	char	*tmp;

	buf = ft_strjoin("minishell: ", str);
	tmp = buf;
	buf = ft_strjoin(buf, ":");
	free(tmp);
	tmp = buf;
	buf = ft_strjoin(buf, " ");
	free(tmp);
	tmp = buf;
	buf = ft_strjoin(buf, strerror(errno));
	free(tmp);
	tmp = buf;
	buf = ft_strjoin(buf, "\n");
	free(tmp);
	write(2, buf, ft_strlen(buf));
	free(buf);
}

/* executes/run all non-buildins trouh execve()
returns -1 if coommand or path to command not found*/
void	ft_execute(t_node *lst, t_env *env)
{
	if (execve(lst->cmds[0], lst->cmds, env->env_vars) == -1)
	{
		if (env->env_path != NULL)
			ft_print_cmd_not_found(lst->cmds[0]);
		if (env->env_path == NULL)
			ft_print_no_file_or_dir(lst->cmds[0]);
		exit(127);
	}
}

/* close all pipes */
void	ft_close_all_pipes(t_exe *exe)
{
	int	i;

	i = 0;
	while (i < exe->num_pipes)
	{
		close(exe->pipes[i][0]);
		close(exe->pipes[i][1]);
		i++;
	}
}
