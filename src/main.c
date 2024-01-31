/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:28:19 by wyap              #+#    #+#             */
/*   Updated: 2024/01/31 18:24:19 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <readline/readline.h>
// #include <readline/history.h>
// // #include <stdbool.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <signal.h>
// #include <string.h> //tmp header, to replace with libft functions
// #include <stdlib.h>
// // #include "/usr/local/opt/readline/include" //(rl_clear_history)
// // /usr/local/opt/readline/lib
#include "../minishell.h"

char	*get_cmd(char *cmd_buf)
{
	char	*prompt;
	char	*cur_path;
	char	*tmp;

	cur_path = ft_strdup("minishell");
	// if ((cur_path = getcwd(NULL, 0)) == NULL)
		// perror("failed to get current working directory\n");
	prompt = ft_strjoin(cur_path, "> ");
	cmd_buf = readline(prompt);
	if (!cmd_buf)
	{
		cmd_buf = "exit";
		// printf("\nexit");
	}
	else if (str_not_empty(cmd_buf))//(ft_strlen(cmd_buf) > 0)
	{
		add_history(cmd_buf);
		printf("jisotry - %s\n", cmd_buf);
		tmp = cmd_buf;
		cmd_buf = ft_strtrim(cmd_buf, " "); //trim space
		free(tmp);
	}
	else if (!str_not_empty(cmd_buf) && (ft_strlen(cmd_buf) > 0))
	{
		add_history(cmd_buf);
		printf("&& - %s\n", cmd_buf);
		tmp = cmd_buf;
		cmd_buf = ft_strtrim(cmd_buf, " "); //trim space
		free(tmp);
	}
	free(prompt);
	free(cur_path);
	return (cmd_buf);
}

t_node **init_lst(t_node **lst_cmd)
{
	lst_cmd = (t_node **)malloc(sizeof(t_node *));
	if (!lst_cmd)
		perror("lst_cmd not allocated");
	*lst_cmd = NULL;
	return (lst_cmd);
}

void	init_env(t_env *env, char **envp)
{
	env->key_count = 0;
	// env->pipe_count = 0;
	store_env(env, envp);
	store_path(env, envp);
	// store_tilda(env, envp);
	// print_env_var(envp, "PATH"); //compare with splitted path
}

int	main(int ac, char **av, char **envp)
{
	char	*cmd_buf;
	t_env	env;
	t_node	**lst_cmd; //list to store parsed cmd

	(void) av;
	signals();
	cmd_buf = NULL;
	if (ac == 1)
	{
		init_env(&env, envp);
		while (1)
		{
			cmd_buf = get_cmd(cmd_buf);
			printf("cmd_buf input:%s\n", cmd_buf);
			if (!ft_strcmp(cmd_buf, "exit"))
				ft_exit(&env, cmd_buf);
			if (check_cmd(cmd_buf) == true)
			{
				lst_cmd = init_lst(lst_cmd);
				ft_parse(lst_cmd, cmd_buf, ft_index(cmd_buf)); //to optimize function
				// printf("\tparse:\n"); print_list(lst_cmd);
				assign_attr(lst_cmd); //whileloop to assign attribute and quote type in node
				// printf("\tassign attr:\n"); print_list(lst_cmd);
				if (check_operator(lst_cmd) == true)
				{
					ft_expand(lst_cmd, &env); //expand handle dollar sign (loop through list and replace env var)
					// printf("\n\texpand:\n"); print_list(lst_cmd);
					trim_quotes(lst_cmd);
					// printf("\n\ttrim quotes:\n"); print_list(lst_cmd);
					clear_empty_node(lst_cmd);
					// printf("\n\tremove null node:\n"); print_list(lst_cmd);
					set_rdr_nodes(lst_cmd);
					// printf("\n\tset rdr:\n"); print_list(lst_cmd);
					combine_nodes(lst_cmd);
					// printf("\n\tcombine:\n"); print_list(lst_cmd);
					set_builtin_nodes(lst_cmd);
					// printf("\n\tset builtin:\n"); print_list(lst_cmd);
					combine_nodes(lst_cmd);
					// printf("\n\tcombine 2:\n"); print_list(lst_cmd);				/*execution*/
					create_cmd_group(&env, *lst_cmd);
					printf("created cmd group\n");
					printf("\n\tcreate_cmd_group:\n"); print_list(lst_cmd); print_cmd_group(lst_cmd);
					execute_cmd(&env, lst_cmd);

					// if (!ft_strncmp(cmd_buf, "echo", 4))
					// 	echo_print(cmd_buf);
					// else if (!ft_strcmp(cmd_buf, "pwd"))
					// 	print_env_var(envp, "PWD");
					// else if (!ft_strcmp(cmd_buf, "env"))
					// 	print_sys_env(&env);
					// else if (!ft_strcmp(cmd_buf, "export"))
					// 	ft_export(&env, "AAAAA=\'aaaaaa\' _b=\"xaxaxax\" __c=0812734917 @_d=\"xaxaxax\" _e6=\"xaxaxax\" f^=\"xaxaxax\" 3g=\"xaxaxax\"");
					// else if (!ft_strcmp(cmd_buf, "unset"))
					// 	ft_unset(&env, "AAAAA _b __c");
				}
				free(cmd_buf); //readline malloc buffer
				free_list(lst_cmd);
				free(lst_cmd);
				lst_cmd = NULL;
			}
			else
				free(cmd_buf); //readline malloc buffer
		}
	}
}

// gcc *.c -lreadline && ./a.out

/*
Q: why not scanf()?
A: will not accept enter as input, has no history capabilities
*/

/*piping info/exercise*/
// int	main(int ac, char **av, char **envp)
// {
// 	char *cmd1[] = {"/bin/ls", 0};
// 	char *cmd2[] = {"/usr/bin/wc", 0};
// 	int fd[2];


// 	pipe(fd);

// 	int i = fork();
// 	if ( i == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO); // fd[1] write or in
// 		close(fd[1]);
// 		close(fd[0]);
// 		execve(cmd1[0], cmd1, envp);
// 	}
// 	else
// 	{
// 		dup2(fd[0], STDIN_FILENO); // fd[0] read or out
// 		close(fd[1]);
// 		close(fd[0]);
// 		execve(cmd2[0], cmd2, envp);
// 		perror("error"); // should be "zsh: command not found: ..."
// 	}
// }
