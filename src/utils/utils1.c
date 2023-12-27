/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 01:12:54 by wyap              #+#    #+#             */
/*   Updated: 2023/12/27 17:45:47 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sighandler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
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
		printf("\tNode Index		:%d", tmp->index);
		printf("\n\tNode Content		:%s", tmp->content);
		printf("\n\tCurr Node Addr		:%p", tmp);
		printf("\n\tPrev Node Addr		:%p", tmp->prev);
		printf("\n\tNext Node Addr		:%p\n\n", tmp->next);
		tmp = tmp->next;
	}
}
