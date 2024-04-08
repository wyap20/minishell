/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_multiline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:58:07 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 14:57:50 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*for heredoc*/

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

char	*read_multiline_input(char *delim)
{
	char	*line;
	char	*multi;
	int		count;

	multi = NULL;
	count = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delim))
		{
			if (!line && g_hdflag == 0)
				printf("minishell: warning: here-document delimited"
					" by end-of-file (wanted `%s')\n", delim);
			free(line);
			break ;
		}
		else if (line && ft_strcmp(line, delim))
		{
			multi = join_lines(multi, line, count);
			count++;
		}
	}
	return (multi);
}

char	*get_multiline(char *delim)
{
	char	*multi;
	int		tmp_fd;
	char	*tmp;

	multi = NULL;
	tmp_fd = dup(STDIN_FILENO);
	signal(SIGINT, sig_hd);
	multi = read_multiline_input(delim);
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	tmp = multi;
	multi = ft_strjoin(tmp, "\n");
	free(tmp);
	return (multi);
}
