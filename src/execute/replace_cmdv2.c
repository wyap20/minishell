/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_cmdv2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:38:57 by atok              #+#    #+#             */
/*   Updated: 2024/01/27 16:00:32 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_get_cmd_path(char **path, char *cmd)
{
	char	*a;
	char 	*b;
	int 	i;	
	
	i = 0;
	a = ft_strjoin("/",cmd);
	while(path[i] != 0x00)
	{
		b = ft_strjoin(path[i],a);
		if(access(b,F_OK) == 0)
		{
			free(a);
			return (b);
		}
		else
			free(b);
		i++;
	}
	free(a);
	return(ft_strdup(cmd));
}

// when use: create_cmd_group(&env, (*lst_cmd));
void	create_cmd_group(t_env *env, t_node *lst_cmd)
{
	t_node	*ptr;
	char	*tmp;

	ptr = lst_cmd;
	while (ptr)
	{
		tmp = NULL;
		ptr->cmds = ft_split(ptr->content, ' ');
		if (!ptr->cmds[0])
			return ;
		tmp = ptr->cmds[0];
		if (ft_strcmp(ptr->attr, "builtin"))
		{
			ptr->cmds[0] = ft_get_cmd_path(env->paths, ptr->cmds[0]);
			free(tmp);
		}
		// for (int i = 0; ptr->cmds[i]; i++) //in uncomment valgrind will have invalid read
		// 	printf("ptr->cmd[%d]: %s\n", i, ptr->cmds[i]);
		ptr = ptr->next;
	}
}
// size_t	get_new_size(t_node *node, char **cmds)
// {
// 	size_t	node_size = sizeof(t_node);
// 	size_t	content_size = sizeof(char *);
// 	content_size += sizeof(char) * (ft_strlen(node->content) + 1);

// 	size_t string_count = get_array_count(cmds);
// 	printf("string_count: %zu\n", string_count);
// 	size_t	cmd_size = sizeof(char **);
// 	cmd_size += sizeof(char *) * string_count;
// 	for (size_t i = 0; i < string_count; i++)
// 		cmd_size += sizeof(char) * (ft_strlen(cmds[i]) + 1);
	
// 	size_t new_size = node_size + content_size + cmd_size;
// 	return (new_size);
// }

//when use: create_cmd_group(&env, (lst_cmd));
// t_node *create_cmd_group(t_env *env, t_node *lst_cmd)
// {
//     t_node    *ptr;
//     char    **tmp;
//     char    *path;
//     char    *tmp2;

//     ptr = lst_cmd;
//     while (ptr)
//     {
//         tmp = NULL;
//         if (!ft_strcmp(ptr->attr, "none") || !ft_strcmp(ptr->attr, "rdr"))
//         {
//             // printf("%ld\n", sizeof(ptr));
//             // ptr->cmds = ft_split(ptr->content, ' ');
//             // printf("%ld\n", sizeof(ptr->cmds));
//             // tmp = ptr->cmds[0];
//             // ptr->cmds[0] = ft_get_cmd_path(env->paths, ptr->cmds[0]);
//             // free(tmp);

//             tmp = ft_split(ptr->content, ' ');
//             path = ft_get_cmd_path(env->paths, tmp[0]);
//             tmp2 = tmp[0];
//             tmp[0] = path;
//             free(tmp2);
//             for (int i = 0; tmp[i]; i++) //in uncomment valgrind will have invalid read
//                 printf("tmp[%d]: %s\n", i, tmp[i]);
//             size_t new_size = get_new_size(ptr, tmp);
// // printf("new_size: %zu\n", new_size);
//             printf("cur:%p\nprev:%p\nnext:%p\n", ptr, ptr->prev, ptr->next);
//             t_node *new = realloc(ptr, new_size);
//             if (!new)
//             {
//                 printf("realloc failed\n");
//                 break ;
//             }
//             else
//             {
// 				printf("%p\n", new);
// 				if (!(new->prev)) //if head node
// 				{
// 					if (new->next)
// 						new->next->prev = new;
//                     lst_cmd = new;
// 				}
//                 if (new->prev) //if there's a prev node
//                     new->prev->next = new;
//                 ptr = new;
//                 // if (!(ptr->prev)) //if head node
//                 //     lst_cmd = ptr;
//                 ptr->cmds = tmp;
//                 printf("REALLOC\ncur:%p\nprev:%p\nnext:%p\n", ptr, ptr->prev, ptr->next);
//             }
//             for (int i = 0; ptr->cmds[i]; i++) //in uncomment valgrind will have invalid read
//                     printf("ptr->cmd[%d]: %s\n", i, ptr->cmds[i]);
//             // free_2d_arr(tmp);
//         }
//         // for (int i = 0; ptr->cmds[i]; i++) //in uncomment valgrind will have invalid read
//         //     printf("ptr->cmd[%d]: %p\n", i, ptr->cmds[i]);
//         ptr = ptr->next;
//     }
// 	return (lst_cmd);
// }



// int	main(int ac, char **av, char **envp)
// {
// 	char *tmp;
// 	char **path;
// 	char *buffer;
// 	char *output;
// 	int i;

// 	i = 0;
// 	while (envp[i] != 0x00)
// 	{
// 		if (!ft_strncmp(envp[i], "PATH=", 5))
// 			// printf("%s\n", envp[i]);
// 		tmp = ft_substr(envp[i], 5, (int)ft_strlen(envp[i]) - 5);
// 		i++;
// 	}
// 	// printf("%s\n", tmp);
// 	path = ft_split(tmp,':');
// 	// i = 0;
// 	// while(path[i] != 0x00)
// 	// 	printf("%s\n", path[i++]);

// 	// ft_get_cmd_path(path,cmd);
// //--------------------------------------

// 	char *result;
// 	char cmd[] = "z"; // << if no valid cmd path will get erro "freeing address wihch is not allocated"
// 	result = ft_get_cmd_path(path,cmd);
// 	printf("%s\n",result);

// 	// free 2D path, 1D tmp & 1D result
// 	i = 0;
// 	while (path[i] != 0x00)
// 		free(path[i++]);
// 	free(path);
// 	free(tmp);
// 	free(result);
	
// 	return(0);
// }
