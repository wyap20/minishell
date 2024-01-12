/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:05:50 by wyap              #+#    #+#             */
/*   Updated: 2024/01/09 15:23:25 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
* combine nodes that is not operator or commands
* !!: DIRECT LEAK DETECTED IN WSL
*/
void	combine_nodes(t_node **lst_cmd)
{
	t_node	*ptr;
	t_node	*tmp;
	t_node	*tmp2;

	ptr = *lst_cmd;
	while (ptr)
	{
		if (!ft_strcmp(ptr->attr, "none") || !ft_strcmp(ptr->attr, "space"))
		{
			if (ptr->prev && (!ft_strcmp(ptr->prev->attr, "none") || !ft_strcmp(ptr->prev->attr, "space")))
			{
					ptr->prev->content = ft_strjoin(ptr->prev->content, ptr->content);
					ptr->prev->next = ptr->next;
					if (ptr->next)
						ptr->next->prev = ptr->prev;
					tmp = ptr;
					ptr = ptr->prev;
					// free(tmp);
					free_node(tmp);
			}
		}
		else if (!ft_strcmp(ptr->attr, "builtin") || !ft_strcmp(ptr->attr, "operator"))
		{
			tmp2 = ptr->next;
			if (tmp2 && (!ft_strcmp(tmp2->attr, "none") || !ft_strcmp(tmp2->attr, "space")))
			{
					ptr->content = ft_strjoin(ptr->content, tmp2->content);
					ptr->next = tmp2->next;
					if (tmp2->next)
						tmp2->next->prev = ptr;
					// tmp = ptr->next;
					// free(tmp2);
					free_node(tmp2);
			}
		}
		if (ptr && ptr->next)
			ptr = ptr->next;
		else
			break ;
	}
}

// void	free_node(t_node *node)
// {
// 	// free(node->attr);
// 	free(node->content);
// 	free(node->next);
// 	free(node->prev);
// 	// free(node->quote_type);
// 	free(node);
// }

/*combine nodes that is not operator or commands*/
// void	combine_nodes(t_node **lst_cmd)
// {
// 	t_node 	*ptr;
// 	t_node	*tmp;

// 	ptr = *lst_cmd;
// 	while (ptr)
// 	{
// 		if (!ft_strcmp(ptr->attr, "none") || !ft_strcmp(ptr->attr, "space"))
// 		{
// 			if (ptr->prev && (!ft_strcmp(ptr->prev->attr, "none") || !ft_strcmp(ptr->prev->attr, "space")))
// 			{
// 					ptr->prev->content = ft_strjoin(ptr->prev->content, ptr->content);
// 					ptr->prev->next = ptr->next;
// 					if (ptr->next)
// 						ptr->next->prev = ptr->prev;
// 					tmp = ptr;
// 					ptr = ptr->prev;
// 					// free(tmp);
// 					free_node(tmp);
// 			}
// 		}
// 		else if (!ft_strcmp(ptr->attr, "builtin") || !ft_strcmp(ptr->attr, "operator"))
// 		{
// 			if (ptr->next && (!ft_strcmp(ptr->next->attr, "none") || !ft_strcmp(ptr->next->attr, "space")))
// 			{
// 					ptr->content = ft_strjoin(ptr->content, ptr->next->content);
// 					ptr->next = ptr->next->next;
// 					if (ptr->next->next)
// 						ptr->next->next->prev = ptr;
// 					tmp = ptr->next;
// 					// free(tmp);
// 					free_node(tmp);
// 			}
// 		}
// 		if (ptr && ptr->next)
// 			ptr = ptr->next;
// 		else
// 			break ;
// 	}
// }

/*combine nodes between operator and/or commands*/
// void	combine_nodes(t_node **lst_cmd)
// {
// 	t_node 	*ptr;
// 	t_node	*tmp1;
// 	t_node	*tmp2;
// 	int		count = 0;
// 	// char	*addr_left;
// 	// char	*addr_right;

// 	ptr = *lst_cmd;
// 	tmp1 = NULL;
// 	tmp2 = NULL;
// 	while (ptr)
// 	{
// 		if ((!ft_strcmp(ptr->attr, "operator") || !ft_strcmp(ptr->attr, "builtin")) && count < 1)
// 		{
// 			tmp1 = ptr;
// 			ptr = ptr->next;
// 		}
// 		if ( || !ft_strcmp(ptr->attr, "space"))// && !(ptr->prev))
// 		{
// 			// tmp1 = NULL;
// 			count = 1; //count++;
// 		}
// 		// while (ptr->next && (!ft_strcmp(ptr->next->attr, "none") || !ft_strcmp(ptr->next->attr, "space"))) //loop until next cmd/operator
// 		while (ptr->next && (ft_strcmp(ptr->next->attr, "operator") || ft_strcmp(ptr->next->attr, "builtin"))) //loop until next cmd/operator
// 		{
// 			// if ()
// 			ptr = ptr->next;
// 			count++;
// 		}
// 		printf("\ncount:%d\n", count);
// 		printf("addr:%p\nattr:%s\n\n", ptr, ptr->attr);
// 		if (!ft_strcmp(ptr->attr, "operator") || !ft_strcmp(ptr->attr, "builtin"))// && count > 1)
// 		{
// 			printf("mark0\n");
// 			tmp2 = ptr;
// 		}
// 		printf("tmp1:%p\ntmp2:%p\n", tmp1, tmp2);
// 		if (tmp1 && tmp2)
// 		{
// 			printf("count:%d\n", count);
// 			ptr = tmp1->next;
// 			while (ptr->next) //(ptr != tmp2 && ptr->next)
// 			{
// 				if (ptr->next != tmp2)
// 					ptr->content = ft_strjoin(ptr->content, ptr->next->content);
// 				if (ptr->next == tmp2)
// 					ptr->next = tmp2;
// 				if (ptr->next && ptr->next->next)
// 					ptr->next = ptr->next->next;
// 				if (ptr->next)
// 				{
// 					free(ptr->next->prev); //cant free node if next is null
// 					ptr->next->prev = ptr;
// 				}
// 				printf("joined:%s\n", ptr->content);
// 			}
// 			printf("mark1\n");
// 			if (ptr == tmp2)
// 			{
// 				printf("mark2\n");
// 				tmp1 = tmp2;
// 				tmp2 = NULL;
// 				ptr = *lst_cmd;
// 				break ;
// 			}
// 		}
// 		ptr = ptr->next;
// 	}

// }


//separate to 3 parts?
//combine front
//combine middle
//combine back