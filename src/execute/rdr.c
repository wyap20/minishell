/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:23:21 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 16:25:00 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* convert string to an fd to mimic heredoc */
int	ft_here_doc(char *str)
{
	int	io[2];
	int	len;

	len = 0;
	if (str)
	{
		while (str[len] != 0x00)
			len++;
		pipe(io);
		write(io[1], str, len);
		close(io[1]);
	}
	else
	{
		pipe(io);
		close(io[1]);
	}
	return (io[0]);
}

/* join string before writing to a std_err */
void	ft_if_open_failed(char *str)
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

/* handles left redirections */
void	ft_redir_left(t_exe *exe, t_node *lst, t_env *env)
{
	if (ft_strcmp(lst->cmds[0], "<") == 0)
	{
		exe->redir[0] = open(lst->cmds[1], O_RDONLY);
		if (exe->redir[0] == -1)
		{
			ft_if_open_failed(lst->cmds[1]);
			env->err_num = 1;
			exit(1);
		}
		dup2(exe->redir[0], STDIN_FILENO);
		close(exe->redir[0]);
	}
	else if (ft_strcmp(lst->cmds[0], "<<") == 0)
	{
		exe->redir[0] = ft_here_doc(lst->cmds[1]);
		dup2(exe->redir[0], STDIN_FILENO);
		close(exe->redir[0]);
	}
}

/* handles right redirections */
void	ft_redir_right(t_exe *exe, t_node *lst)
{
	if (ft_strcmp(lst->cmds[0], ">") == 0)
	{
		exe->redir[1] = open(lst->cmds[1], O_WRONLY | O_CREAT
				| O_TRUNC, 0666);
		dup2(exe->redir[1], STDOUT_FILENO);
		close(exe->redir[1]);
	}
	else if (ft_strcmp(lst->cmds[0], ">>") == 0)
	{
		exe->redir[1] = open(lst->cmds[1], O_WRONLY | O_CREAT
				| O_APPEND, 0666);
		dup2(exe->redir[1], STDOUT_FILENO);
		close(exe->redir[1]);
	}
}
