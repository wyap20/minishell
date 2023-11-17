/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:28:19 by wyap              #+#    #+#             */
/*   Updated: 2023/11/17 23:07:36 by wyap             ###   ########.fr       */
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

void	print_sys_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return ;
}

void	print_env_var(char **envp, char *s)
{
	int		i;
	char	**pwd;

	i = -1;
	pwd = NULL;
	s = ft_strjoin(s, "=");
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], s, 4))
		{
			pwd = ft_split(envp[i], '=');
			break ;
		}
	}
	printf("%s\n", pwd[1]);
}

static void	sighandler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}
void	echo_print(const char *str)
{
	int	i;

	i = 4;
	while (str[++i])
		printf("%c", str[i]);
	printf("\n");
}

int	main(int ac, char **av, char **envp)
{
	(void) av;
	char	*cmd_buf;
	char	*prompt;
	char	*cur_path;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN); //ignore ctrl + '\'
	if (ac == 1)
	{
		while (1)
		{
			if ((cur_path = getcwd(NULL, 0)) == NULL)
				perror("failed to get current working directory\n");
			prompt = ft_strjoin(cur_path, "> ");
			cmd_buf = readline(prompt);
			if (cmd_buf == NULL)
			{
				cmd_buf = "exit";
				printf("\nexit");
			}
			if (ft_strlen(cmd_buf) > 0){ //carriage return will not be added
				if (cmd_buf[0] == ' ')
					continue;
				add_history(cmd_buf);
			}
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
				free(cur_path); //getcwd malloc
				rl_clear_history();
				exit(1);
			}
			// else  //if invalid command; create a 2d array of command keywords to match?
			// 	printf("[minishell] %s: command not found\n", cmd_buf);
		}
	}
}

// gcc *.c -lreadline && ./a.out

/*
Q: why not scanf()?
A: will not accept enter as input, has no history capabilities
*/