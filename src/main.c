/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:28:19 by wyap              #+#    #+#             */
/*   Updated: 2023/12/28 17:19:25 by wyap             ###   ########.fr       */
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

	if ((cur_path = getcwd(NULL, 0)) == NULL)
		perror("failed to get current working directory\n");
	prompt = ft_strjoin(cur_path, "> ");
	cmd_buf = readline(prompt);
	if (cmd_buf == NULL)
	{
		cmd_buf = "exit";
		printf("\nexit");
	}
	if (ft_strlen(cmd_buf) > 1){ //carriage return will not be added
		if (cmd_buf[0] != ' ')
			add_history(cmd_buf);
			// continue;
		cmd_buf = ft_strtrim(cmd_buf, " "); //trim space
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
		store_env(&env, envp);
		store_path(&env, envp);
		// print_env_var(envp, "PATH"); //compare with splitted path
		while (1)
		{
			cmd_buf = get_cmd(cmd_buf);
			if (check_cmd(cmd_buf) == true)
			{
				lst_cmd = init_lst(lst_cmd);
				ft_parse(lst_cmd, cmd_buf, ft_index(cmd_buf)); //to optimize function
				print_list(lst_cmd);
				assign_attr(lst_cmd);
				print_list(lst_cmd);
				ft_expand(lst_cmd, &env);
			//function: whileloop to assign attribute and quote type in node
			//expand handle dollar sign (loop through list and replace env var)

			/*execution*/
				// parse_pipe(cmd_buf);
				// printf("cmd_buf: %s\n", cmd_buf);
				// printf("%d\n", ft_strncmp(cmd_buf, "echo", 4) == 0);
				if (!ft_strncmp(cmd_buf, "echo", 4)) //works but incorrect implementation
					echo_print(cmd_buf);
				else if (!ft_strcmp(cmd_buf, "pwd"))
					print_env_var(envp, "PWD");
				else if (!ft_strcmp(cmd_buf, "env"))
					print_sys_env(envp);
				else if (!ft_strcmp(cmd_buf, "exit"))
				{
					free(cmd_buf); //readline malloc buffer
					// free(lst_cmd);
					rl_clear_history(); //-I /usr/local/opt/readline/include -L /usr/local/opt/readline/lib
					exit(1);
				}
			// else  //if invalid command; create a 2d array of command keywords to match?
			// 	printf("[minishell] %s: command not found\n", cmd_buf);
			}
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
