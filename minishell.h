#ifndef MINISHELL
# define MINISHELL

#include <readline/readline.h>
#include <readline/history.h>
// #include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h> //tmp header, to replace with libft functions
#include <stdlib.h>
// #include "/usr/local/opt/readline/include" //(rl_clear_history)
// /usr/local/opt/readline/lib

/*libft + custom utils*/
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

int		ft_strcmp(char *s1, char *s2);

#endif