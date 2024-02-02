#include "../../minishell.h"

char	*join_lines(char *multi, char *line, int count)
{
	char	*tmp;

	if (count == 0)
	{
		multi = ft_strdup(line);
		free(line);
	}
	else if (count > 0)
	{
		tmp = multi;
		multi = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = multi;
		multi = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	return (multi);
}

char	*get_multiline(char	*delim)
{
	char	*line;
	char	*multi;
	char	*tmp;
	int		count;

	multi = NULL;
	count = 0;
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		else if (line && ft_strcmp(line, delim))
		{
			multi = join_lines(multi, line, count);
			count++;
		}
	}
	tmp = multi;
	multi = ft_strjoin(tmp, "\n");
	free(tmp);
	return (multi);
}

// char	*get_multiline(char	*str)
// {
// 	char	*line;
// 	char	*multi;
// 	char	*tmp;
// 	int		count;

// 	multi = NULL;
// 	count = 0;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!ft_strcmp(line, str))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		else if (line && ft_strcmp(line, str))
// 		{
// 			if (count == 0)
// 			{
// 				multi = ft_strdup(line);
// 				free(line);
// 				count++;
// 			}
// 			else if (count > 0)
// 			{
// 				tmp = multi;
// 				multi = ft_strjoin(tmp, "\n");
// 				free(tmp);
// 				tmp = multi;
// 				multi = ft_strjoin(tmp, line);
// 				free(tmp);
// 				free(line);
// 				count++;
// 			}
// 		}
// 	}
// 	tmp = multi;
// 	multi = ft_strjoin(tmp, "\n");
// 	free(tmp);
// 	// printf("multi:\n%s$\n********\n", multi);
// 	return (multi);
// }