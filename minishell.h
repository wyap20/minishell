#ifndef MINISHELL
# define MINISHELL

#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// #include <readline.h>
// #include <history.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
// #include "/usr/local/opt/readline/include" //(rl_clear_history)
// /usr/local/opt/readline/lib

extern int g_hdflag;

/*
node struct:
int index
char *data //parsed string
char *quote {(null), single (s), double (d)} 
char *attr {(null), builtin (b), external (e), flag (f), operator (o)}
prev
next
*/
typedef	struct s_node{
	char	*content;
	char	*quote_type;
	char	*attr;
	char	**cmds;
	struct	s_node	*next;
	struct	s_node	*prev;
}t_node;

typedef struct s_env{
	char	**env_vars;
	char	*env_path;
	char	*home_tilde;
	char	**paths;
	int		err_num;
	int		key_count;
}t_env;

typedef struct s_exe
{
	int		num_pipes;
	int		num_cmds;
	int		(*pipes)[2];
	int		z;
	int		redir[2];
	int		status;
	pid_t	*pid;
}	t_exe;

/*libft + basic utils*/
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
int	ft_isalnum(int c);
int	ft_isupper(int c);

int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_isalpha(int c);
char	*ft_itoa(int n);

/*RT's doubly list proto*/
t_node	*ft_dlstnew(char *data);
void	ft_dlstadd_front(t_node **lst, t_node *new);
void	ft_dlstadd_back(t_node **lst, t_node *new);
int		ft_dlstsize(t_node	*lst);
t_node	*ft_dlstlast(t_node *lst);

/*sighandler*/
void	signals(void);
void	sig_hd(int sig);
void	sig_nl(int sig_num);

/*utils*/
void	free_node(t_node *node);
void	free_list(t_node **lst_cmd);
void	free_2d_arr(char **arr);
bool	str_not_empty(const char *str);
void	print_sys_env(t_env *env);

// void	print_nodes(t_node **lst_cmd);
// void	print_list(t_node **lst);
// void	print_cmd_group(t_node **lst);

// parsing
bool	check_cmd(t_env *env, char *cmd_str);
int	ft_check_quote(char *str);
bool	ft_check_arrow(char *str);
int	*ft_index(char *cmd_buf);
int	*ft_quote_pair(int *out, char *str);
int	*ft_index_quote(int *out, char *str);
int	*ft_index_left_arrow(int *out, char *str);
int	*ft_index_right_arrow(int *out, char *str);
void	ft_parse(t_node **lst_cmd ,char *cmd_buf, int *int_array);
void	assign_attr(t_node **lst_cmd);
bool	check_operator(t_env *env, t_node **lst_cmd);
void	trim_quotes(t_node **lst_cmd);
void	clear_empty_node(t_node **lst_cmd);
void	set_rdr_nodes(t_node **lst_cmd);
void	combine_nodes(t_node **lst_cmd);
// void	set_builtin_nodes(t_node **lst_cmd);
void ft_sort(t_node *lst);

// expanding
void	store_env(t_env *env, char **envp);
void	store_path(t_env *env);
void	store_tilde(t_env *env);
void	ft_expand(t_node **lst_cmd, t_env *env);
char	*expand_errno(t_env *env, char *key);


/*expand utils*/
char *ft_strcpy(char *dst, char *src);
int ft_not_alpha(char c);
char *ft_strstr(char *str, char*ss);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t n);

/*execute*/
char	*get_multiline(char	*delim);
int		create_cmd_group(t_env *env, t_node *lst_cmd);
void	get_pipe_count(t_exe *exe, t_node **lst_cmd);
void	ft_execute_cmd(t_env *env, t_node **lst);
void	ft_initialize_exe_vars(t_exe *exe, t_node **lst);
void	ft_sort(t_node *lst);
void	ft_if_no_pipes(t_exe *exe, t_node *lst, t_env *env);
void	ft_close_all_pipes(t_exe *exe);
void	ft_multi_pipe(t_exe *exe, t_node *lst, t_env *env);
void	run_builtin(t_env *env, t_node *ptr, char type);

void	ft_redir_right(t_exe *exe, t_node *lst);
void	ft_redir_left(t_exe *exe, t_node *lst, t_env *env);
void	ft_close_all_pipes(t_exe *exe);
void	ft_execute(t_node *lst, t_env *env);



/*built in*/
void	echo_print(char **cmds);
void	ft_export(t_env *env, char **cmds, char type);
char	**check_export(char **add, t_env *env, char type);
void	add_to_env(t_env *env, char **updated);
void	ft_unset(t_env *env, char **cmds);
void	ft_exit(t_env *env, char *cmd_buf);
// void ft_cd(t_env *env, char **input);
void	ft_cd(t_env *env, char **input, char type);
void	ft_pwd(void);

/*built in utils*/
int	get_array_count(char **array);
char	*get_env_home(t_env *env);


#endif