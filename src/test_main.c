/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:28:19 by wyap              #+#    #+#             */
/*   Updated: 2023/11/16 13:13:07 by wyap             ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) env;
	char	*cmd_buf;
	char	*prompt;
	char	*cur_path;

	cur_path = "path_placeholder"; //string to get path, shell prompt
	if (ac == 1)
	{
		while (1)
		{
			// printf("%s> ", cur_path);
			// scanf("%s", cmd_buf); //forbidden function, only for testing
			prompt = ft_strjoin(cur_path, "> ");
			cmd_buf = readline(prompt);
			// if (ft_strlen(cmd_buf) > 0) //carriage return will not be added
			// 	add_history(cmd_buf);
			if (!strcmp(cmd_buf, "exit"))
				break ;
			// free(cmd_buf); //readline malloc buffer
		}
	}
}

// gcc *.c -lreadline && ./a.out

/*
Q: why not scanf()?
A: will not accept enter as input, has no history capabilities
*/