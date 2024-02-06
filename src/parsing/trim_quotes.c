/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:28:19 by wyap              #+#    #+#             */
/*   Updated: 2024/01/05 15:37:34 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	trim_inner_quotes(t_node *ptr)
{
	int		i;
	int		j;
	int		len;
	char	quote;

	i = 0;
	j = 0;
	len = ft_strlen(ptr->content);
	// if (!ft_strcmp(ptr->quote_type, "none"))
	// 	return ;
	if (!ft_strcmp(ptr->quote_type, "double"))
		quote = '\"';
	else if (!ft_strcmp(ptr->quote_type, "single"))
		quote = '\'';
	while (i < len)
	{
		if (ptr->content[i] == quote && ptr->content[i + 1] == quote)
			i++;
		else
			ptr->content[j++] = ptr->content[i];
		i++;
	}
	ptr->content[j] = '\0';
}

void	trim_quotes(t_node **lst_cmd)
{
	t_node	*ptr;
	char	*quote;
	char	*tmp;

	ptr = *lst_cmd;
	tmp = NULL;
	while (ptr)
	{
		while (!ft_strcmp(ptr->quote_type, "none") && ptr->next)
			ptr = ptr->next;
		if (!ft_strcmp(ptr->quote_type, "none") && ptr->next == NULL)
			break ;
		if (!ft_strcmp(ptr->quote_type, "double"))
			quote = "\"";
		else if (!ft_strcmp(ptr->quote_type, "single"))
			quote = "\'";
		tmp = ptr->content;
		ptr->content = ft_strtrim(ptr->content, quote);
		free(tmp);
		// if (ft_strlen(ptr->content) == 3 && ptr->content[0] == quote[0]
		// 	&& ptr->content[2] == quote[0]) //parse string with 1 char;
		// {
		// 	tmp = ptr->content;
		// 	ptr->content = ft_substr(ptr->content, 1, 1);
		// 	free(tmp);
		// }
		// printf("%lu\n", ft_strlen(ptr->content));
		trim_inner_quotes(ptr);
		ptr = ptr->next;
	}
}

// void	trim_quotes(t_node **lst_cmd)
// {
// 	t_node	*ptr;

// 	ptr = *lst_cmd;
// 	while (ptr)
// 	{
// 		if (!ft_strcmp(ptr->quote_type, "double"))
// 			ptr->content = ft_strtrim(ptr->content, "\"");
// 		else if (!ft_strcmp(ptr->quote_type, "single"))
// 			ptr->content = ft_strtrim(ptr->content, "\'");
// 		if ((!ft_strcmp(ptr->quote_type, "double")
// 				|| !ft_strcmp(ptr->quote_type, "single"))
// 			&& ft_strlen(ptr->content) == 3) //parse string with 1 char;
// 			ptr->content = ft_substr(ptr->content, 1, 1);
// 		// printf("%lu\n", ft_strlen(ptr->content));
// 		trim_inner_quotes(ptr);
// 		ptr = ptr->next;
// 	}
// }

void	clear_empty_node(t_node **lst_cmd)
{
	t_node	*ptr;
	t_node	*tmp;

	ptr = *lst_cmd;
	while (ptr)
	{
		tmp = ptr->next;
		if (ft_strlen(ptr->content) == 0)
		{
			if (ptr->prev) //is not NULL
				ptr->prev->next = ptr->next;
			else
				*lst_cmd = ptr->next;
			if (ptr->next)
				ptr->next->prev = ptr->prev;
			free_node(ptr);
		}
		ptr = tmp;
	}
}
