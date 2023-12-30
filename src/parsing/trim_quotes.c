#include "../../minishell.h"

void	trim_quotes(t_node **lst_cmd)
{
	t_node	*ptr;

	ptr = *lst_cmd;
	while (ptr)
	{
		if (!ft_strcmp(ptr->quote_type, "double"))
			ptr->content = ft_strtrim(ptr->content, "\"");
		if (!ft_strcmp(ptr->quote_type, "single"))
			ptr->content = ft_strtrim(ptr->content, "\'");
		if ((!ft_strcmp(ptr->quote_type, "double") || !ft_strcmp(ptr->quote_type, "single")) && ft_strlen(ptr->content) == 3)
			ptr->content = ft_substr(ptr->content, 1, 1);
		printf("%lu\n", ft_strlen(ptr->content));
		ptr = ptr->next;	
	}
}

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
			free(ptr);
		}
		ptr = tmp;
	}
}
