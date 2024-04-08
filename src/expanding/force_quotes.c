#include "../../minishell.h"

void	force_quotes(t_node *ptr)
{
	char	*tmp;

	tmp = ptr->content;
	ptr->content = ft_strjoin("\"", ptr->content);
	free(tmp);
	tmp = ptr->content;
	ptr->content = ft_strjoin(ptr->content, "\"");
	free(tmp);
}
