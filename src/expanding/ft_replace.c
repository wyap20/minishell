/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:52:12 by wyap              #+#    #+#             */
/*   Updated: 2023/12/28 14:52:12 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_replace (char *str, char *key, char *val)
{
	// printf("\n[replace]\nstr:%s\nkey:%s\nval:%s\n\n", str, key, val);
	if (val == NULL)
		val = "\0";
	// if slen val = 0 //when there is no such key
	// if slen val <= slen key // when val is <= key len
	int len = ft_strlen(str)+ft_strlen(val); // most lazy and efficient way
	// int len = ft_strlen(str)-ft_strlen(key)+ft_strlen(val);
	char *ns = malloc(sizeof(char) * (len + 1));
	
	ft_strcpy(ns, str);

	char *ptr = ft_strstr(ns, key);
	// int i = 0;
	// while (str[i] != *ptr)
	// 	i++;
	if (ptr)
	{
		//dst will be where the end of val is. src wiil be end of key. n will be wehre key/src end
		// moving the raminder to the back remainder=anyhong after key)
		// ft_strncpy (ns, str, i);
		ft_memmove (ptr+ft_strlen(val), ptr+ft_strlen(key), ft_strlen(ptr+ft_strlen(key))+1);
		ft_strncpy (ptr, val, ft_strlen(val));
		// free(str);
	}
	return (ns);
}

char	*get_key(t_node *token)
{
	char	*key;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = token->content;
	key = NULL;
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			i++;
			j++;
			while (tmp[i] != ' ' && tmp[i] != '$' && tmp[i])
			{
				i++;
				j++;
			}
			printf("\n");
			key = ft_substr(tmp, i - j, j);
			if (ft_strlen(key) > 0)
				break ;
		}
		i++;
	}
	printf("get key:%s\n", key);
	return (key);
}

char	*expand_errno(t_env *env, char *key)
{
	char	*err_no;
	char	*sub;
	char	*val;

	err_no = ft_itoa(env->err_num);
	sub = ft_substr(key, 2, ft_strlen(key) - 1);
	val = ft_strjoin(err_no, sub);
	// printf("key:%s\n", key);
	// printf("itoa errnum:%s\n", err_no);
	// printf("sub:%s\n", sub);
	// printf("expand errno val:%s\n", val);
	return (free(sub), free(err_no), val);
}

char	*get_val(t_env *env, char *key)
{
	int		i;
	int		len;
	char	*val;
	char	*trim;

	i = 0;
	if (key[0] == '$' && key[1] == '?')
	{
		val = expand_errno(env, key);
		return (val);
	}
	trim = ft_strtrim(key, "$");
	key = ft_strjoin(trim, "=");
	len = (int)ft_strlen(key);
	printf("get_val key:%s\nlen:%i\n", key, len);
	val = NULL;
	while (env->env_vars[i])//[0])
	{
		if (!ft_strncmp(env->env_vars[i], key, len))
			val = ft_substr(env->env_vars[i], len, (int)ft_strlen(env->env_vars[i]) - len);
		i++;
	}
	return (free(trim), free(key), val);
}
	// printf("**View stored env**\n");
	// for (int j = 0; env->env_vars[j][0]; j++)
	// 	printf("%d: %s\n", j, env->env_vars[j]);

// bool check_dollar(const char *str)
// {
// 	int i;
	
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$')
// 		{
// 			if (str[i + 1] == '\"' || !ft_not_alpha(str[i + 1]))
// 				return false; //nothing left to replace
// 		}
// 		i++;
// 	}
// 	  return true;
// }

void	get_key_val_rplc(t_env *env, t_node *ptr)
{
	char	*key;
	char	*val;
	char	*tmp;

	key = get_key(ptr);
	if (key != NULL && key[0] == '$' && ((ft_not_alpha(key[1]) && key[1] != '?') || !key[1]))
	{
		ptr = ptr->next;
		return (free(key));
	}
	else if (key != NULL)
	{
		tmp = key;
		key = ft_strtrim(key, "\"\'");
		free(tmp);
		printf("trim:%s\n", key);
		val = get_val(env, key);
		// printf("val:%s\n", val);
		tmp = ptr->content;
		ptr->content = ft_replace(ptr->content, key, val);
		free(tmp);
		free(key);
		free(val);
	}
}

void	ft_expand(t_node **lst_cmd, t_env *env)
{
	t_node	*ptr;
	char	*tmp;

	ptr = *lst_cmd;
	tmp = NULL;
	while (ptr)
	{
		if (!ft_strcmp(ptr->content, "~") && !ft_strcmp(ptr->quote_type, "none"))
		{
			tmp = ptr->content;
			ptr->content = ft_strdup("$HOME");
			free(tmp);
		}
		if (!ft_strcmp(ptr->quote_type, "double") || !ft_strcmp(ptr->quote_type, "none")) //if is double or open quote
			get_key_val_rplc(env, ptr);
		// if (ptr)
			// if (!ft_strcmp(ptr->quote_type, "single") || !ft_strchr(ptr->content, '$')) 
		ptr = ptr->next;
		// printf("expandmark\n");
	}
}

// void	ft_expand(t_node **lst_cmd, t_env *env)
// {
// 	t_node	*ptr;
// 	char	*key;
// 	char	*val;
// 	char	*tmp;

// 	ptr = *lst_cmd;
// 	while (ptr)
// 	{
// 		if (!ft_strcmp(ptr->quote_type, "double") || !ft_strcmp(ptr->quote_type, "none")) //if is double or open quote
// 		{
// 			key = get_key(ptr);
// 			// printf("key0:%d\nkey1:%d\n", key[0], key[1]);
// 			// printf("%d\n", ft_not_alpha(key[1]));
// 			//handle standalone '$'
// 			if (key != NULL && key[0] == '$' && (ft_not_alpha(key[1]) || !key[1]))
// 				ptr = ptr->next;
// 			else if (key != NULL)
// 			{
// 				tmp = key;
// 				key = ft_strtrim(key, "\"\'");
// 				free(tmp);
// 				printf("trim:%s\n", key);
// 				val = get_val(env, key);
// 				printf("val:%s\n", val);
// 				tmp = ptr->content;
// 				ptr->content = ft_replace(ptr->content, key, val);
// 				free(tmp);
// 				free(key);
// 				free(val);
// 			}
// 		}
// 		if (ptr)
// 			if (!ft_strcmp(ptr->quote_type, "single") || !ft_strchr(ptr->content, '$')) 
// 				ptr = ptr->next;
// 		// printf("expandmark\n");
// 	}
// }

// int main(void)
// {
// 	// char arg[]= "atok";
// 	// char *$USER = arg;
// 	// char *$USER = "atok";
// 	// printf("hi%s\n", $USER);

// 	// char *intput = "echo $test 42";
// 	// char *$test = "42 kl is muy home";
// 	// char *$output = "echo 42 kl is muy home 42";

// 	// char *str = "echo me$USER";
// 	char *str = "echo me$USERme xop";
// 	// char *str = "echo me$USER me";
// 	// char *str = "echo me$USER test$USER";


// 	// char *key = "$USER";
// 	char *key = "$USERme";
// 	// char *val = "tok";
// 	// char *val = "";
// 	char *val = "usernameisatok";
// 	char *ns;

// 	ns = ft_replace(str,key,val);
// 	printf("%s\n",ns);
// 	free(ns);
// 	return(0);
// }

// while loop input find $
// substr $... return it as char *key
// for val, use key to find val


// echo hello world | wc

// node1
// Cmd_string = echo hello world
// Cmd_array = {echo, hello, world. NULL}
// redir1
// redirype = <<
// redirtext = end
//    heredoc = ""

// node 2
// Cmd_string = wc
// Cmd_array = {wc NULL}

// node1
// echo
// node2
// hello
// node3
// world
// node4
// |
// node5
// wc

// check node until | or end
// array {echo, NULL}
// array {echo,world,NULL}
// array {echo,world,hello,NULL}

// | -> run Cmd 

// array {wc, NULL}

// \0 -> run Cmd


