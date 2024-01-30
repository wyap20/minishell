/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:44:59 by wyap              #+#    #+#             */
/*   Updated: 2024/01/30 21:34:28 by atok             ###   ########.fr       */
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

/*have not handle cases if PWD OLDPWD is unset*/
void	update_pwd_oldpwd(t_env *env, char **pwd)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = -1;
	while (env->env_vars[++i])
	{
		if (!ft_strncmp(env->env_vars[i], "PWD=", 4))
		{
			tmp = env->env_vars[i];
			env->env_vars[i] = pwd[0];
		}
	}
	if (!tmp) //if no PWD
	{
		tmp = ft_strjoin("PWD=", pwd[0]);
		ft_export(env, tmp);
		free(tmp);
	}
	i = -1;
	while (env->env_vars[++i])
	{
		if (!ft_strncmp(env->env_vars[i], "OLDPWD=", 4))
		{
			tmp = env->env_vars[i];
			env->env_vars[i] = pwd[0];
		}
	}

}

// [cd] [~] or [cd] [NULL]
void ft_cd(t_env *env, t_exe *exe, char **input)
{
	char	*home_path;
	// char	**split;

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
	else if (input[1][0] == '~')
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