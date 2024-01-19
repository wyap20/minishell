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

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <string.h>
#include "../../minishell.h"

// ft_mememove
// ft_strcpy
// ft_strncpy
// ft_strstr

char *ft_strcpy(char *dst, char *src)
{
	int i;

	i = 0;
	while(src[i] != 0x00)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0x00;
	return (dst);
}

int ft_not_alpha(char c)
{
	// if (c == ' ' || c == '\'' || c == '\"' || c == '|' || c == '<' || c == '>' || c == '$')
	if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
		return 1;
	else 
		return 0;
}

char *ft_strstr(char *str, char*ss)
{
	int i;
	int j;

	i = 0;
	while (str[i] != 0x00)
	{
		j = 0;
		while (str[i + j] == ss[j] && str[i + j] != 0x00)  //handle edge/end case
		{	
			// if (ss[j] == 0x00) 
			// 	return ((char *) str + i);
			j++;
		}
        if (ss[j] == 0x00 && ft_not_alpha(str[i + j]) == 1) // && str[i] == delim? space squo dquot 
            return ((char *)str + i);
		i++;
	}
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ud;
	unsigned char	*us;

	ud = (unsigned char *)dest;
	us = (unsigned char *)src;
	if (ud == NULL && us == NULL)
		return (NULL);
	i = 0;
	if (ud < us)
		while (i < n--)
			(*ud++) = (*us++);
	else
	{
		while (n > i)
		{
			ud[n - 1] = us[n - 1];
			n--;
		}
	}
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != 0x00)
	{
		dest[i] = src[i];
		i++;	
	}
	while (i < n) 
	{
		dest[i] = 0x00;
		i++;
	}
	return (dest);
}


char	*ft_replace (char *str, char *key, char *val)
{
	// printf("\n[replace]\nstr:%s\nkey:%s\nval:%s\n\n", str, key, val);
	if (val == NULL)
		val = "\0";
	// if slen val = 0 //when there is no such key
	// if slen val <= slen key // when val is <= key len
	int len = strlen(str)+strlen(val); // most lazy and efficient way
	// int len = strlen(str)-strlen(key)+strlen(val);
	char *ns = malloc(sizeof(char) * (len + 1));
	
	ft_strcpy (ns, str);

	char *ptr = ft_strstr (ns, key);
	// int i = 0;
	// while (str[i] != *ptr)
	// 	i++;
	if (ptr)
	{
		//dst will be where the end of val is. src wiil be end of key. n will be wehre key/src end
		// moving the raminder to the back remainder=anyhong after key)
		// ft_strncpy (ns, str, i);
		ft_memmove (ptr+strlen(val), ptr+strlen(key), strlen(ptr+strlen(key))+1);
		ft_strncpy (ptr, val, strlen(val));
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
		// if (tmp[i] == '$' && (tmp[i + 1] == '\"' || tmp[i + 1]))
		// 	return (NULL);
		if (tmp[i] == '$')
		{
			i++;
			j++;
			while (tmp[i] != ' ' && tmp[i] != '$' && tmp[i])
			{
				// printf("mark");
				i++;
				j++;
			}
			printf("\n");
			key = ft_substr(tmp, i - j, j);
			if (strlen(key) > 0)
				break ;
		}
		i++;
	}
	// printf("get key:%s\n", key);
	return (key);
}

char	*get_val(t_env *env, char *key)
{
	int		i;
	int		len;
	char	*val;

	i = 0;
	key = ft_strjoin(ft_strtrim(key, "$"), "=");
	len = (int)ft_strlen(key);
	// printf("get_val key:%s\nlen:%i\n", key, len);
	val = NULL;
	while (env->env_vars[i])//[0])
	{
		if (!ft_strncmp(env->env_vars[i], key, len))
			val = ft_substr(env->env_vars[i], len, (int)ft_strlen(env->env_vars[i]) - len);
		i++;
	}
	return (val);
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

void	ft_expand(t_node **lst_cmd, t_env *env)
{
	t_node	*ptr;
	char	*key;
	char	*val;

	ptr = *lst_cmd;
	while (ptr)
	{
		if (!ft_strcmp(ptr->quote_type, "double") || !ft_strcmp(ptr->quote_type, "none")) //if is double or open quote
		{
			key = get_key(ptr);
			if (key != NULL)// && ft_strcmp(key, "$")) //if not null and key is not "$"
			{
				key = ft_strtrim(key, "\"\'");
				// printf("trim:%s\n", key);
				val = get_val(env, key);
				// printf("val:%s\n", val);
				ptr->content = ft_replace(ptr->content, key, val);
			}
		}
		//if is single quote or there's no more $ to replace
		// if (!ft_strcmp(ptr->quote_type, "single") || !(check_dollar(ptr->content) == false))
		if (!ft_strcmp(ptr->quote_type, "single") || !ft_strchr(ptr->content, '$')) 
			ptr = ptr->next;
		// printf("expandmark\n");
	}
}

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


