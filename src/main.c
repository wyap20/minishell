/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:28:19 by wyap              #+#    #+#             */
/*   Updated: 2024/02/22 18:02:22 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_hdflag = 0;

char	*get_cmd(char *cmd_buf)
{
	char	*tmp;

	cmd_buf = readline("minishell> ");
	if (!cmd_buf)
		cmd_buf = "exit";
	else if (str_not_empty(cmd_buf))
	{
		tmp = cmd_buf;
		cmd_buf = ft_strtrim(cmd_buf, " ");
		free(tmp);
	}
	else if (!str_not_empty(cmd_buf) && (ft_strlen(cmd_buf) > 0))
	{
		add_history(cmd_buf);
		tmp = cmd_buf;
		cmd_buf = ft_strtrim(cmd_buf, " ");
		free(tmp);
	}
	return (cmd_buf);
}
	// else if (str_not_empty(cmd_buf)) //if only contain whitespace

	// cur_path = NULL;
	// if ((cur_path = getcwd(NULL, 0)) == NULL)
		// perror("failed to get current working directory\n");
	// prompt = ft_strjoin(cur_path, "> ");
	// cmd_buf = readline(prompt);
	//...
	// free(prompt);
	// free(cur_path);

t_node	**init_lst(t_node **lst_cmd)
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
	env->err_num = 0;
	env->env_vars = NULL;
	env->env_path = NULL;
	env->paths = NULL;
	env->home_tilde = NULL;
	store_env(env, envp);
	store_path(env);
	store_tilde(env);
}

void	lexer_seq(t_env *env, t_node **lst_cmd, char *cmd_buf)
{
	ft_parse(lst_cmd, cmd_buf, ft_index(cmd_buf));
	assign_attr(lst_cmd);
	if (check_operator(env, lst_cmd) == true)
	{
		ft_expand(*lst_cmd, env);
		if (*lst_cmd)
		{
			set_rdr_nodes(*lst_cmd);
			combine_nodes(lst_cmd);
			ft_sort(*lst_cmd);
			combine_nodes(lst_cmd);
			if (create_cmd_group(env, *lst_cmd) == 0)
				ft_execute_cmd(env, lst_cmd);
		}
	}
	free(cmd_buf);
	free_list(lst_cmd);
	free(lst_cmd);
	lst_cmd = NULL;
}

int	main(int ac, char **av, char **envp)
{
	char	*cmd_buf;
	t_env	env;
	t_node	**lst_cmd;

	(void) av;
	cmd_buf = NULL;
	if (ac == 1)
	{
		init_env(&env, envp);
		while (1)
		{
			g_hdflag = 0;
			signals();
			cmd_buf = get_cmd(cmd_buf);
			if (!ft_strcmp(cmd_buf, "exit"))
				ft_exit(&env, cmd_buf);
			if (check_cmd(&env, cmd_buf) == true)
			{
				lst_cmd = init_lst(lst_cmd);
				lexer_seq(&env, lst_cmd, cmd_buf);
			}
			else
				free(cmd_buf);
		}
	}
}

/*
Q: why not scanf()?
A: will not accept enter as input, has no history capabilities
*/