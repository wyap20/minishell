/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:44:59 by wyap              #+#    #+#             */
/*   Updated: 2024/02/13 13:54:06 by wyap             ###   ########.fr       */
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
			ret = ft_substr(env->env_vars[i], 5,
					(int)ft_strlen(env->env_vars[i]) - 5);
	}
	return (ret);
}

void	update_oldpwd(t_env *env, char *oldpwd)
{
	int		i;
	char	*oldpwd_ptr;
	char	**export;

	i = -1;
	oldpwd_ptr = NULL;
	while (env->env_vars[++i])
	{
		if (!ft_strncmp(env->env_vars[i], "OLDPWD=", 7))
		{
			oldpwd_ptr = env->env_vars[i];
			env->env_vars[i] = ft_strjoin("OLDPWD=", oldpwd);
			free(oldpwd_ptr);
			free(oldpwd);
		}
	}
	if (!oldpwd_ptr)
	{
		export = (char **)malloc(2 * sizeof(char *));
		export[0] = ft_strjoin("OLDPWD=", oldpwd);
		export[1] = NULL;
		ft_export(env, export);
		free_2d_arr(export);
		free(oldpwd);
	}
}

void	export_pwd(t_env *env, char *pwd)
{
	char	*pwd_ptr;
	char	**export;

	pwd_ptr = NULL;
	export = NULL;
	pwd_ptr = ft_strjoin("PWD=", pwd);
	export = (char **)malloc(3 * sizeof(char *));
	export[0] = pwd_ptr;
	export[1] = ft_strdup("OLDPWD=");
	export[2] = NULL;
	ft_export(env, export);
	free_2d_arr(export);
	free(pwd);
}

void	update_pwd_oldpwd(t_env *env, char *pwd)
{
	int		i;
	char	*pwd_ptr;
	char	**split;

	pwd_ptr = NULL;
	i = -1;
	while (env->env_vars[++i])
	{
		if (!ft_strncmp(env->env_vars[i], "PWD=", 4))
		{
			pwd_ptr = env->env_vars[i];
			env->env_vars[i] = ft_strjoin("PWD=", pwd);
			free(pwd);
		}
	}
	if (!pwd_ptr)
		export_pwd(env, pwd);
	if (pwd_ptr)
	{
		split = ft_split(pwd_ptr, '=');
		update_oldpwd(env, ft_strdup(split[1]));
		free_2d_arr(split);
	}
	free(pwd_ptr);
}

void	change_dir(t_env *env, char **input)
{
	char	*home_path;

	home_path = get_env_home(env);
	if (input[1] && input[2])
	{
		printf("minishell: cd: too many arguments\n");
		exit(1);
	}
	if (input[1] == NULL)
	{
		if (home_path)
			env->err_num = chdir(home_path);
		else
		{
			printf("minishell: cd: HOME not set\n");
			exit(1);
		}
	}
	else
		env->err_num = chdir(input[1]);
	free(home_path);
}

void	ft_cd(t_env *env, char **input)
{
	char	*pwd;

	pwd = NULL;
	change_dir(env, input);
	if (env->err_num == 0)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			perror("failed to get current working directory\n");
		update_pwd_oldpwd(env, pwd);
	}
	else
	{
		printf("minishell: cd: %s: %s\n", input[1], strerror(errno));
		exit(1);
	}
}
