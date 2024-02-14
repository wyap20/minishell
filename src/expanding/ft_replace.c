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

/*
* replacing a substring with another substring
* parameter: string to check for substring
* key: the substring that will be replaced by 'val' substring
* val: the substring that replaces the 'key' substring
* returns string with key substr replaced by val
*/
char	*ft_replace(char *str, char *key, char *val)
{
	int		len;
	char	*new;
	char	*ptr;

	len = 0;
	new = NULL;
	if (val == NULL)
		val = "\0";
	len = ft_strlen(str) + ft_strlen(val);
	new = (char *)malloc(sizeof(char) * (len + 1));
	ft_strcpy(new, str);
	ptr = ft_strstr(new, key);
	if (ptr)
	{
		ft_memmove(ptr + ft_strlen(val), ptr + ft_strlen(key),
			ft_strlen(ptr + ft_strlen(key)) + 1);
		ft_strncpy(ptr, val, ft_strlen(val));
	}
	return (new);
}
//ptr: tells the index position of the key
//strnpcy
//dst will be where the end of val is. src wiil be end of key.
//n will be wehre key/src end
// moving the raminder to the back remainder=anyhong after key)

// char	*get_key(t_node *token)
// {
// 	char	*key;
// 	char	*tmp;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = 0;
// 	tmp = token->content;
// 	key = NULL;
// 	while (tmp[++i])
// 	{
// 		if (tmp[i] == '$')
// 		{
// 			i++;
// 			j++;
// 			while (tmp[i] != ' ' && tmp[i] != '$' && tmp[i]
// 				&& (ft_isalpha(tmp[i]) || tmp[i] == '?'))
// 			{
// 				i++;
// 				j++;
// 			}
// 			key = ft_substr(tmp, i - j, j);
// 			if (ft_strlen(key) > 0)
// 				break ;
// 		}
// 	}
// 	return (key);
// }

char	*get_key(t_node *t)
{
	char	*key;
	int		i;
	int		j;

	i = -1;
	j = 0;
	key = NULL;
	while (t->content[++i])
	{
		if (t->content[i] == '$')
		{
			i++;
			j++;
			while (t->content[i] != ' ' && t->content[i] != '$' && t->content[i]
				&& (ft_isalpha(t->content[i]) || t->content[i] == '?'))
			{
				i++;
				j++;
			}
			key = ft_substr(t->content, i - j, j);
			if (ft_strlen(key) > 0)
				break ;
		}
	}
	return (key);
}
	// printf("get key:%s\n", key);

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
	val = NULL;
	while (env->env_vars[i])
	{
		if (!ft_strncmp(env->env_vars[i], key, len))
			val = ft_substr(env->env_vars[i], len,
					(int)ft_strlen(env->env_vars[i]) - len);
		i++;
	}
	return (free(trim), free(key), val);
}
	// printf("**View stored env**\n");
	// for (int j = 0; env->env_vars[j][0]; j++)
	// 	printf("%d: %s\n", j, env->env_vars[j]);

t_node	*get_key_val_rplc(t_env *env, t_node *ptr)
{
	char	*key;
	char	*val;
	char	*tmp;

	key = get_key(ptr);
	if (key != NULL && key[0] == '$'
		&& ((ft_not_alpha(key[1]) && key[1] != '?') || !key[1]))
		return (free(key), ptr->next);
	else if (key != NULL)
	{
		tmp = key;
		key = ft_strtrim(key, "\"\'");
		free(tmp);
		val = get_val(env, key);
		tmp = ptr->content;
		ptr->content = ft_replace(ptr->content, key, val);
		free(tmp);
		free(key);
		free(val);
	}
	return (ptr);
}
		// printf("trim:%s\n", key);
		// printf("val:%s\n", val);

// void	ft_expand(t_node **lst_cmd, t_env *env)
// {
// t_node	*ptr;
// char	*tmp;

// ptr = *lst_cmd;
// tmp = NULL;
// while (ptr)
// {
// if (!ft_strcmp(ptr->content, "~") && !ft_strcmp(ptr->quote_type, "non"))
// {
// tmp = ptr->content;
// ptr->content = ft_strdup(env->home_tilde);
// free(tmp);
// }
// else if (ptr->content[0] == '~' && ptr->content[1] != '~')
// {
// tmp = ptr->content;
// ptr->content = ft_replace(ptr->content, "~", env->home_tilde);
// free(tmp);
// }
// else if (!ft_strcmp(ptr->quote_type, "d")
// || !ft_strcmp(ptr->quote_type, "non"))
// ptr = get_key_val_rplc(env, ptr);
// if (ptr)
// if (!ft_strcmp(ptr->quote_type, "s") || !ft_strchr(ptr->content, '$'))
// 	ptr = ptr->next;
// }
// }
		// printf("expandmark\n");

void	ft_expand(t_node *lst, t_env *env)
{
	char	*tmp;

	tmp = NULL;
	while (lst)
	{
		if (!ft_strcmp(lst->content, "~") && !ft_strcmp(lst->quote_type, "non"))
		{
			tmp = lst->content;
			lst->content = ft_strdup(env->home_tilde);
			free(tmp);
		}
		else if (lst->content[0] == '~' && lst->content[1] != '~')
		{
			tmp = lst->content;
			lst->content = ft_replace(lst->content, "~", env->home_tilde);
			free(tmp);
		}
		else if (!ft_strcmp(lst->quote_type, "d")
			|| !ft_strcmp(lst->quote_type, "non"))
			lst = get_key_val_rplc(env, lst);
		if (lst)
			if (!ft_strcmp(lst->quote_type, "s")
				|| !ft_strchr(lst->content, '$'))
				lst = lst->next;
	}
}
		// printf("expandmark\n");