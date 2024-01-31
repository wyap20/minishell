/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 01:12:54 by wyap              #+#    #+#             */
/*   Updated: 2024/01/30 21:21:20 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sighandler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN); //ignore ctrl + '\'
}

// void print_nodes(t_node **lst_cmd)
// {
// 	t_node *ptr;
// 	int i;

// 	i = 0;
// 	ptr = *lst_cmd;
// 	while (ptr)
// 	{
// 		printf("%d:%s\n", i, ptr->content);
// 		ptr = ptr->next;
// 		i++;
// 	}
// }

void	print_list(t_node **lst)
{
	t_node *tmp;

	tmp = *lst;
	printf("\n\t***lst_cmd***\n");
	while (tmp)
	{
		// printf("\tNode Index		:%d", tmp->index);
		printf("\n\tNode Content		:%s", tmp->content);
		printf("\n\tAttribute		:%s", tmp->attr);
		printf("\n\tQuote Type		:%s", tmp->quote_type);
		printf("\n\tCurr Node Addr		:%p", tmp);
		printf("\n\tPrev Node Addr		:%p", tmp->prev);
		printf("\n\tNext Node Addr		:%p\n", tmp->next);
		tmp = tmp->next;
	}
}

void	print_cmd_group(t_node **lst)
{
	t_node	*ptr;

	ptr = *lst;

	printf("\n\t***PRINT CMD GROUP***");
	while (ptr)
	{
		printf("\n\tCurr Node Addr		:%p", ptr);
		if (ptr->cmds)
			for (int i = 0; ptr->cmds[i]; i++)
				printf("\n\tcmd[%d]:%s", i, ptr->cmds[i]);
		printf("\n\n");
		ptr = ptr->next;
	}
}

/*free malloc all strings then free malloc of 2D array
* !!! INSPECT FURTHER, COULD BE CAUSE OF MEMORY LEAKS
*/
void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr[i]);
	free(arr);
}

void	free_node(t_node *node)
{
	// free(node->attr); //no malloc
	free(node->content);
	free_2d_arr(node->cmds);
	// free(node->next); //cannot free next node?
	// free(node->prev); //cannot free prev node?
	// free(node->quote_type); //no malloc
	free(node);
}

void	free_list(t_node **lst_cmd)
{
	t_node *ptr = *lst_cmd;
	t_node *tmp;

	while (ptr)
	{
		tmp = ptr->next;
		free_node(ptr);
		ptr = tmp;
	}
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

bool	str_not_empty(const char *str)
{
	// int	i;

	// if (!str)
	// 	return (false);
	// i = 0;
	// while (str[i])
	// {
	// 	if (!is_whitespace(str[i]))
	// 		return (true);
	// 	i++;
	// }
	// return (false);
	int i = 0;
	while(str[i])
	{
		if(is_whitespace(str[i]))
			i++;
		else
			return(false);
	}
	return(true);
}