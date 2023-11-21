#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char *cmd1[] = {"/bin/ls", "-a", 0}; //argv
	char *cmd2[] = {"/usr/bin/wc", 0};

	int fd[2], pid1, pid2;

	if (pipe(fd) < 0)
	{
		perror("pipe fail");
		return 1;
	}
	pid1 = fork();
	if (pid1 < 0) //main
		return 2;
	if (pid1 == 0) //child
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(cmd1[0], cmd1, envp);
	}
	pid2 = fork();
	if (pid2 < 0) //main
		return 3;
	if (pid2 == 0) //child
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execve(cmd2[0], cmd2, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}