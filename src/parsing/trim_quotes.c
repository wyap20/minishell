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


