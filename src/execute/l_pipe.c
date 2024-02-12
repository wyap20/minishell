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

/* convert string to an fd to mimic heredoc */
int	ft_here_doc(char *str)
{
	int	io[2];
	int	len;

	len = 0;
	while (str[len] != 0x00)
		len++;
	pipe(io);
	write(io[1], str, len);
	close(io[1]);
	return (io[0]);
}

/* initialize varaible used in execution */
void	ft_initialize_exe_vars(t_exe *exe, t_node **lst)
{
	exe->num_pipes = 0;
	exe->num_cmds = 0;
	get_pipe_count(exe, lst);
	exe->num_cmds = ft_dlstsize(*lst);
	exe->redir[0] = -2;
	exe->redir[1] = -2;
	exe->z = 0;
	exe->pid = malloc((exe->num_pipes + 1) * sizeof(pid_t));
	if (exe->num_pipes > 0)
		exe->pipes = malloc(exe->num_pipes * sizeof(int [2]));
	else if (exe->num_pipes == 0)
		exe->pipes = 0;
}

/* writes to a tmp fd for output to be truncated before writing to std err*/
void	ft_if_open_failed(char *str)
{
	int		tmp;
	int		n;
	char	buf[42];

	tmp = open(str, O_CREAT | O_WRONLY, 0644);
	write(tmp, "minishell> ", 12);
	write(tmp, str, ft_strlen(str));
	write(tmp, ": No such file or directory\n", 29);
	close(tmp);
	tmp = open(str, O_RDONLY);
	while (1)
	{
		n = read(tmp, buf, 42);
		if (n == 0)
			break ;
		write(2, buf, n);
	}
	close(tmp);
	unlink(str);
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

/* executes/run all non-buildins trouh execve()
returns -1 if coommand or path to command not found*/
void	ft_execute(t_exe *exe, t_node *lst, t_env *env) //WIP
{
	if (execve(lst->cmds[0], lst->cmds, env->env_vars) == -1)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		exe->z = ft_strlen(lst->cmds[0]);
		while (exe->z > 0)
		{
			if (lst->cmds[0][exe->z] == '/')
				break ;
			exe->z--;
		}
		// may only need printf for cmd not found and the exit 127 only
		// ls a 
		// in bash ls: cannot access 'a': No such file or directory
		// in ours /bin/ls: cannot access 'a': No such file or directory
		// is auto print err msg by ls itself
		if (env->env_path != NULL)
			printf("%s: command not found\n",
				lst->cmds[0] + exe->z);
		if (env->env_path == NULL)
			printf("minishell: %s: no such file or directory\n",
				lst->cmds[0] + exe->z);
		exit(127);
	}
}

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

/* runs own implementaion of buildin commands as per subject pdf */
void	run_builtin(t_env *env, t_node *ptr)
{
	char	*cmd;

	cmd = ptr->cmds[0];
	if (!ft_strcmp(cmd, "echo"))
		echo_print(ptr->cmds);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd, "env"))
		print_sys_env(env);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(env, ptr->cmds);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(env, ptr->cmds);
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(env, ptr->cmds);
}

/* runs all the command for the groups */
void	ft_run_cmds(t_exe *exe, t_node *lst, t_env *env)
{
	while (lst != NULL && lst->cmds[0][0] != '|')
	{
		if (lst->cmds[0][0] == '<' || lst->cmds[0][0] == '>')
		{
			ft_redir_left(exe, lst, env);
			ft_redir_right(exe, lst);
		}
		else
		{
			if (!ft_strcmp(lst->attr, "builtin"))
				run_builtin(env, lst);
			else
				ft_execute(exe, lst, env);
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
			ft_run_cmds(exe, lst, env);
			exit(0);
		}
		i++;
	}
}

/*part of ft_sort to swap content of 2 nodes */
void	ft_swap_info(t_node *a, t_node *b)
{
	char	**cmds;
	char	*attr;
	char	*content;
	char	*quote_type;

	cmds = a->cmds;
	a->cmds = b->cmds;
	b->cmds = cmds;
	attr = a->attr;
	a->attr = b->attr;
	b->attr = attr;
	content = a->content;
	a->content = b->content;
	b->content = content;
	quote_type = a->quote_type;
	a->quote_type = b->quote_type;
	b->quote_type = quote_type;
}

/* part of ft_sort to preserve sequence/order once a swap happens*/
void	ft_reorder(t_node *dst, t_node *x)
{
	if (dst == x)
		return ;
	else
	{
		while (dst != x)
		{
			ft_swap_info(dst, x);
			dst = dst->next;
		}
	}
}

/* iterate troguh nodes that are in correct position */
t_node	*ft_get_req_node(t_node *x)
{
	while (!ft_strcmp(x->attr, "rdr") && x->next != NULL)
		x = x->next;
	return (x);
}

/* swap and reorder the nodes function */
t_node *ft_swap_reorder(t_node *dst, t_node *x)
{
	ft_swap_info(dst, x);
	dst = dst->next;
	ft_reorder(dst, x);
	return (dst);
}

/* re-arrange commands in each group so that redirections runs 1st */
void	ft_sort(t_node *lst)
{
	t_node	*x;
	t_node	*dst;

	x = lst;
	if (x->next == NULL)
		return ;
	while (x != NULL)
	{
		// while (!ft_strcmp(x->attr,"rdr") && x->next != NULL)
		// 	x = x->next;
		// dst = x;
		x = ft_get_req_node(x);
		dst = x;
		while (x != NULL && ft_strcmp(x->attr, "pipe"))
		{
			if (!ft_strcmp(x->attr, "rdr"))
			{
				if (dst->attr != x->attr)
				{
					// ft_swap_info(dst, x);
					// dst = dst->next;
					// ft_reorder(dst, x);
					dst = ft_swap_reorder(dst, x);
				}
			}
			x = x->next;
		}
		if (x != NULL)
			x = x->next;
	}
}

/* exclusively run when no pipe or only 1 cmd group */
void	ft_if_no_pipes(t_exe *exe, t_node *lst, t_env *env)
{
	if (exe->pipes == 0)
	{
		while (lst != NULL)
		{
			if (!ft_strcmp(lst->attr, "builtin"))
			{
				if (!ft_strcmp(lst->cmds[0], "export") || 
					!ft_strcmp(lst->cmds[0], "unset") || 
					!ft_strcmp(lst->cmds[0], "cd"))
					run_builtin(env, lst);
				return ;
			}
			lst = lst->next;
		}
	}
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
