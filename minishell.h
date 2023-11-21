#ifndef MINISHELL
# define MINISHELL

// #include "libreadline.a"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// #include <readline.h>
// #include <history.h>
// #include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h> //tmp header, to replace with libft functions
#include <stdlib.h>
// #include "/usr/local/opt/readline/include" //(rl_clear_history)
// /usr/local/opt/readline/lib

// typedef struct s_shell{
// 	char	*cmd_buf;
// 	char	*prompt;
// 	char	*cur_path;
// }t_shell;

/*libft + custom utils*/
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
int	ft_isalnum(int c);

int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);

// parsing
int parse_pipe(char *cmd_str);

#endif