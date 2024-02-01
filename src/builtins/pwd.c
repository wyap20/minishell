#include "../../minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	if ((pwd = getcwd(NULL, 0)) == NULL)
		perror("failed to get current working directory\n");
	printf("%s\n", pwd);
	free(pwd);
}
