/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:44:59 by wyap              #+#    #+#             */
/*   Updated: 2024/01/29 16:03:29 by wyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
char	*get_env_home(t_env *env)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = -1;
	while (env->env_vars[++i])
	{
		if (!ft_strncmp(env->env_vars[i], "HOME=", 5))
			ret = ft_substr(env->env_vars[i], 5, (int)ft_strlen(env->env_vars[i]) - 5);
	}
	return (ret);
}

// [cd] [~] or [cd] [NULL]
void ft_cd(t_env *env, t_exe *exe, char **input)
{
	char	*home_path;
	char	**split;

	home_path = get_env_home(env);

	if (input[1] == NULL)// || input[1] == '~')
	{
		if (home_path)
			exe->err_num = chdir(home_path);// parse in HOME=... from env
		else
		{
			//havent update err_num?
			printf("minishell cd: HOME not set\n");
			return ;
		}
	}
	else if (input[1] == '~')
		exe->err_num = chdir(env->home_tilda);
	else
		exe->err_num = chdir(input[1]);
	if (exe->err_num == 0)
	{
		// update PWD=.. in env 
		// add OLDPWD=.. in env
	}
	else
		printf("minishell cd: %s: No such file or directory\n", input[1]);
}

// if cd successfull chdir retunr 0 if not will return 1

//other cases:
//replace ~ with env->home_tilda if path ~/..... ??
//cd -