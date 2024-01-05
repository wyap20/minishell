/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:05:50 by wyap              #+#    #+#             */
/*   Updated: 2024/01/05 20:46:38 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*combine nodes between operator and/or commands*/
void	combine_nodes(t_node **lst_cmd)
{
	t_node 	*ptr;
	t_node	*tmp1;
	t_node	*tmp2;
	int		count = 0;
	// char	*addr_left;
	// char	*addr_right;

	ptr = *lst_cmd;
	tmp1 = NULL;
	tmp2 = NULL;
	while (ptr)
	{
		if ((!ft_strcmp(ptr->attr, "operator") || !ft_strcmp(ptr->attr, "builtin")) && count < 1)
		{
			tmp1 = ptr;
			ptr = ptr->next;
		}
		if (!ft_strcmp(ptr->attr, "none"))// && !(ptr->prev))
		{
			// tmp1 = NULL;
			count = 1; //count++;
		}
		// while (ptr->next && (!ft_strcmp(ptr->next->attr, "none") || !ft_strcmp(ptr->next->attr, "space"))) //loop until next cmd/operator
		while (ptr->next && (ft_strcmp(ptr->next->attr, "operator") || ft_strcmp(ptr->next->attr, "builtin"))) //loop until next cmd/operator
		{
			// if ()
			ptr = ptr->next;
			count++;
		}
		printf("\ncount:%d\n", count);
		printf("addr:%p\nattr:%s\n\n", ptr, ptr->attr);
		if (!ft_strcmp(ptr->attr, "operator") || !ft_strcmp(ptr->attr, "builtin"))// && count > 1)
		{
			printf("mark0\n");
			tmp2 = ptr;
		}
		printf("tmp1:%p\ntmp2:%p\n", tmp1, tmp2);
		if (tmp1 && tmp2)
		{
			printf("count:%d\n", count);
			ptr = tmp1->next;
			while (ptr->next) //(ptr != tmp2 && ptr->next)
			{
				if (ptr->next != tmp2)
					ptr->content = ft_strjoin(ptr->content, ptr->next->content);
				if (ptr->next == tmp2)
					ptr->next = tmp2;
				if (ptr->next && ptr->next->next)
					ptr->next = ptr->next->next;
				if (ptr->next)
				{
					free(ptr->next->prev); //cant free node if next is null
					ptr->next->prev = ptr;
				}
				printf("joined:%s\n", ptr->content);
			}
			printf("mark1\n");
			if (ptr == tmp2)
			{
				printf("mark2\n");
				tmp1 = tmp2;
				tmp2 = NULL;
				ptr = *lst_cmd;
				break ;
			}
		}
		ptr = ptr->next;
	}

}

//separate to 3 parts?
//combine front
//combine middle
//combine back