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

// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/wait.h>
// #include <errno.h>
// #include <string.h> 

// typedef	struct s_node{
// 	char	**cmds;
// 	int		num;
// 	struct	s_node	*next;
// 	struct	s_node	*prev;
// }t_node;

// typedef struct s_exe
// {
// 	int		num_pipes;
// 	int		num_cmds;
// 	int		(*pipes)[2];
// 	int		z;
// 	int		redir[2];
// 	int		status;
// 	int		err_num;
// 	pid_t	*pid;
// }	t_exe;

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	if (s1[i] != s2[i])
// 		return (s1[i] - s2[i]);
// 	return (0);
// }

int	here_doc(char *str)
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

void	sig_nl(int sig_num)
{
	if(sig_num != SIGINT)
		return;
	write(1, "\n", 1);
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	len;

// 	len = 0;
// 	while (str[len] != 0x00)
// 		len++;
// 	return (len);
// }

// t_node **init_lst(t_node **lst)
// {
// 	lst = (t_node **)malloc(sizeof(t_node *));
// 	if (!lst)
// 		perror("lst not allocated");
// 	*lst = NULL;
// 	return (lst);
// }

// t_node *create_node(int num)
// {
// 	t_node *new_node = (t_node *)malloc(sizeof(t_node));
// 	if (!new_node) {
// 		perror("Memory allocation failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	new_node->cmds = NULL;
// 	new_node->num = num;
// 	new_node->next = NULL;
// 	new_node->prev = NULL;
// 	return new_node;
// }
// //=============================================================================
// void ft_gen_node(t_node **lst)
// {
// 	int i = 0;
// 	t_node *current = NULL;

// 	while (i < 5) // <<
// 	{
// 		t_node *new_node = create_node(i);
// 		if (*lst == NULL) 
// 		{
// 			*lst = new_node;
// 		} else 
// 		{
// 			current->next = new_node;
// 			new_node->prev = current;
// 		}
// 		current = new_node;
// 		i++;
// 	}
// }
// //=============================================================================
// void ft_input_node(t_node **lst)
// {
// 	t_node *x = *lst;
	
// 	x->cmds = malloc(2 * sizeof(char*));
// 	x->cmds[0] = "/bin/cat";
// 	x->cmds[1] = NULL;
// 	x = x->next;
	
// 	x->cmds = malloc(2 * sizeof(char*));
// 	x->cmds[0] = "|";
// 	x->cmds[1] = NULL;
// 	x = x->next;
	
// 	x->cmds = malloc(2 * sizeof(char*));
// 	x->cmds[0] = "/bin/cat";
// 	x->cmds[1] = NULL;
// 	x = x->next;
	
// 	x->cmds = malloc(2 * sizeof(char*));
// 	x->cmds[0] = "|";
// 	x->cmds[1] = NULL;
// 	x = x->next;
	
// 	x->cmds = malloc(2 * sizeof(char*));
// 	x->cmds[0] = "/bin/ls";
// 	x->cmds[1] = NULL;

// 	// x->cmds = malloc(3 * sizeof(char*));
// 	// x->cmds[0] = "<";
// 	// x->cmds[1] = "zz";
// 	// x->cmds[2] = NULL;
// 	// x = x->next;

// 	// x->cmds = malloc(3 * sizeof(char*));
// 	// x->cmds[0] = ">>";
// 	// x->cmds[1] = "zzz";
// 	// x->cmds[2] = NULL;
// 	// x = x->next;

// 	// x->cmds = malloc(2 * sizeof(char*));
// 	// x->cmds[0] = "/bin/ls";
// 	// x->cmds[1] = NULL;

// }
//============================================================================
void	ft_initialize_exe_vars(t_exe *exe, t_node **lst)
{
	exe->num_pipes = 0; //<<
	exe->num_cmds = 0; //<<
	get_pipe_count(exe, lst);
	exe->num_cmds = ft_dlstsize(*lst);
	// exe->i = 0;
	// exe->j = 0;
	exe->z = 0;
	exe->err_num = 0;
	exe->pid = malloc((exe->num_pipes + 1) * sizeof(pid_t));
	if (exe->num_pipes > 0)
		exe->pipes = malloc(exe->num_pipes * sizeof(int[2]));
	else if (exe->num_pipes == 0)
		exe->pipes = 0;
}

void	ft_redir_left(t_exe *exe, t_node *lst)
{
	if (ft_strcmp(lst->cmds[0],"<") == 0)
	{
		exe->redir[0] = open(lst->cmds[1], O_RDONLY);
		dup2(exe->redir[0],STDIN_FILENO);
		close(exe->redir[0]);
	}
	else if (ft_strcmp(lst->cmds[0],"<<") == 0)
	{
		exe->redir[0] = here_doc(lst->cmds[1]);
		dup2(exe->redir[0],STDIN_FILENO);
		close(exe->redir[0]);
	}
}

void	ft_redir_right(t_exe *exe, t_node *lst)
{
	if (ft_strcmp(lst->cmds[0], ">") == 0)
	{
		exe->redir[1] = open(lst->cmds[1], O_WRONLY | O_CREAT 
		| O_TRUNC, 0666);
		dup2(exe->redir[1],STDOUT_FILENO);
		close(exe->redir[1]);
	}
	else if (ft_strcmp(lst->cmds[0],">>") == 0)
	{
		exe->redir[1] = open(lst->cmds[1], O_WRONLY | O_CREAT 
		| O_APPEND, 0666);
		dup2(exe->redir[1],STDOUT_FILENO);
		close(exe->redir[1]);
	}
}

void ft_execute(t_exe *exe, t_node *lst, char **envp)
{
	if(execve(lst->cmds[0], lst->cmds, envp) == -1)
	{
		dup2(STDERR_FILENO,STDOUT_FILENO);
		exe->z = ft_strlen(lst->cmds[0]);
		while(exe->z > 0)
		{
			if(lst->cmds[0][exe->z] == '/')
				break;
			exe->z--;
		}
		printf("minishell> %s: command not found\n", 
		lst->cmds[0] + exe->z);
		exe->err_num = 127;
		return ;
	}
	else
	{	
		exe->err_num = 0;
		return ;
	}
}

void ft_set_pipe(t_exe *exe, int i)
{
	if (exe->num_pipes == 0)
	{
		return;
	}
	else
	if (i > 0) // end, mid1; if not first
	{
		dup2(exe->pipes[i - 1][0], STDIN_FILENO);
		close(exe->pipes[i - 1][0]);
		close(exe->pipes[i - 1][1]);
	}
	if (i < exe->num_pipes) // start, mid2; if not last
	{
		dup2(exe->pipes[i][1], STDOUT_FILENO);
		close(exe->pipes[i][0]);
		close(exe->pipes[i][1]);
	}
}

void ft_close_all_pipes (t_exe *exe)
{
	int i;

	i = 0;
	while (i < exe->num_pipes)
	{
		close(exe->pipes[i][0]);
		close(exe->pipes[i][1]);
		i++;
	}
}

void ft_swap_info(t_node *a, t_node *b)
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

// void ft_no_pipe(t_exe *exe, t_node *lst, char **envp)
// {
// 	exe->pid[0] = fork();
// 	while(lst != NULL)
// 	{
// 		// printf("cmd[0]: %s\n",lst->cmds[0]);
// 		if(lst->cmds[0][0] == '<' || lst->cmds[0][0] == '>')
// 		{
// 			ft_redir_left(exe, lst);
// 			ft_redir_right(exe, lst);
// 		}
// 		else 
// 		{
// 			ft_execute(exe, lst, envp);
// 		}
// 		lst = lst->next;
// 	}
// }

void ft_wait_pid (t_exe *exe)
{
	int i;
	int status;

	i = 0;
	while (i < exe->num_pipes + 1)
	{
		if(waitpid(exe->pid[i], &status, 0) > 0)
		{
			if(WIFEXITED(status)) // if child end normally
				exe->err_num = WEXITSTATUS(status);
				// printf("err_num - %d\n",WEXITSTATUS(status));
			else if (WIFSIGNALED(status)) // if child end by signal
				if(WTERMSIG(status) != 0)
					exe->err_num = 130;
					// printf("err_num - 130\n"); // << store for $?
				// printf("err_num - %d\n",WTERMSIG(status)); // retunrns 2

		}
		i++;
	}
}

void ft_free_pp (t_exe *exe)
{
	free(exe->pid);
	if(exe->num_pipes > 0)
		free(exe->pipes);
}

void ft_exe_pipe(t_exe *exe)
{
	int i;

	i = 0;
	while(i < exe->num_pipes)
	{
		if(pipe(exe->pipes[i]) == -1)
			perror("pipe");
		i++;
	}
}

void ft_run_cmds(t_exe *exe, t_node *lst, char **envp)
{
	while (lst != NULL && lst->cmds[0][0] != '|')
	{
		if(lst->cmds[0][0] == '<' || lst->cmds[0][0] == '>')
		{
			ft_redir_left(exe, lst);
			ft_redir_right(exe, lst);
		}
		else 
		{
			//if build in
				//run build in
			//else
				ft_execute(exe, lst, envp);
		}
		lst = lst->next;
	}
}

t_node *ft_get_group(t_node *lst, int i)
{
	if(i != 0)
	{
		while(lst->cmds[0][0] != '|')
		{
			lst = lst->next;
		}
		lst = lst->next;
	}
	return(lst);
}

void ft_multi_pipe(t_exe *exe, t_node *lst, char **envp)
{
	int	i;

	i = 0;
	ft_exe_pipe(exe);
	while (i < exe->num_pipes + 1)
	{
		lst = ft_get_group(lst,i);
		// printf("%d\n",lst->num);
		printf("%s\n",lst->cmds[0]);
		// list not iteratin to next one stuck on 1st group
		exe->pid[i] = fork();
		if (exe->pid[i] == 0)
		{
			ft_set_pipe(exe,i);
			ft_close_all_pipes(exe);
			ft_run_cmds(exe,lst,envp);
			// printf("%s\n",strerror(errno));
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	execute_cmd(t_env *env, t_node **lst)
{
	t_exe	exe;


	ft_initialize_exe_vars(&exe, lst);
	// get_pipe_count(&exe, lst);
	// exe.num_cmds = ft_dlstsize(*lst);
	signal(SIGINT,sig_nl);
	// if (exe.num_pipes == 0)
	// 	ft_no_pipe(&exe, *lst, env->env_vars);
	// else
		ft_multi_pipe(&exe,*lst, env->env_vars);
	ft_close_all_pipes(&exe);
	// if (exe.num_pipes > 0)
		ft_wait_pid(&exe);
	ft_free_pp(&exe);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_exe	exe;
// 	t_node **lst;

// 	lst = init_lst(lst);
// 	ft_gen_node(lst);
// 	ft_input_node(lst);

// 	// t_node *x = *lst;
// 	// while(x != NULL)
// 	// {
// 	// 	printf("%d\n",x->num);
// 	// 	printf("%s\n",x->cmds[0]);
// 	// 	x = x->next;
// 	// }
	
// 	ft_initialize_exe_vars(&exe);
// 	get_pipe_count(&exe, lst);
// 	signal(SIGINT,sig_nl);
// 	if (exe.num_pipes == 0)
// 		ft_no_pipe(&exe, *lst, envp);
// 	else
// 		ft_multi_pipe(&exe,*lst, envp);
// 	ft_close_all_pipes(&exe);
// 	ft_wait_pid(&exe);
// 	ft_free_pp(&exe);

// 	t_node *current = *lst; //head node
// 	while(current != NULL)
// 	{
// 		t_node *tmp = current; // preserve current node
// 		current = current->next; // move to next node
// 		free(tmp->cmds); // free current cmds array
// 		// int i = 0
// 		// while tmp->cmds[i] != 0x00
// 		// 	free(tmp->cmds[i++]);
// 		free(tmp); // free current node itself
// 	}
// 	free(lst);
// 	// *lst = NULL;
// 	return 0;
// }