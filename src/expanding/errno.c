/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:07:09 by wyap              #+#    #+#             */
/*   Updated: 2024/02/14 16:18:24 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_errno(t_env *env, char *key)
{
	char	*err_no;
	char	*sub;
	char	*val;

	err_no = ft_itoa(env->err_num);
	sub = ft_substr(key, 2, ft_strlen(key) - 1);
	val = ft_strjoin(err_no, sub);
	return (free(sub), free(err_no), val);
}
	// printf("key:%s\n", key);
	// printf("itoa errnum:%s\n", err_no);
	// printf("sub:%s\n", sub);
	// printf("expand errno val:%s\n", val);
