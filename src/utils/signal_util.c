/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:53:00 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 15:18:30 by wyap             ###   ########.fr       */
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

/*signal handler in parent process*/
void	signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}
// signal(SIGQUIT, SIG_IGN); //ignore ctrl + '\'

/*heredoc sighandler*/
void	sig_hd(int sig)
{
	int	null_fd;

	if (sig != SIGINT)
		return ;
	g_hdflag = 1;
	null_fd = open("/dev/null", O_RDONLY);
	dup2(null_fd, STDIN_FILENO);
	close(null_fd);
}
