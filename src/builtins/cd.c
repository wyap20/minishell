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

/*memory leak here*/
void	update_oldpwd(t_env *env, char *oldpwd)
{
	int		i;
	char	*oldpwd_ptr;
	char	**split;
	char	**export;

	i = -1;
	oldpwd_ptr = NULL;
	export = NULL;
	split = ft_split(oldpwd, '=');
	free(oldpwd);
	oldpwd = ft_strdup(split[1]);
	free(split);
	printf("entered update oldpwd\n");
	while (env->env_vars[++i]) //if have OLDPWD
	{
		if (!ft_strncmp(env->env_vars[i], "OLDPWD=", 7))
		{
			oldpwd_ptr = env->env_vars[i];
			env->env_vars[i] = ft_strjoin("OLDPWD=", oldpwd);
			free(oldpwd_ptr);
			free(oldpwd);
			printf("updated OLDPWD\n");
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
	// free(oldpwd);
}

void	export_pwd(t_env *env, char *pwd)
{
	char	*pwd_ptr;
	char	**export;

	pwd_ptr = NULL;
	export = NULL;
	printf("ft_cd: PWD not set\n");
	pwd_ptr = ft_strjoin("PWD=", pwd);
	export = (char **)malloc(3 * sizeof(char *)); //3 if oldpwd
	export[0] = pwd_ptr;
	export[1] = ft_strdup("OLDPWD=");
	export[2] = NULL;
	ft_export(env, export);
	printf("ft_cd: exported PWD & OLDPWD (OLDPWD=[blank])\n");
	free_2d_arr(export);
	free(pwd);
}

/*have not handle cases if PWD OLDPWD is unset*/
void	update_pwd_oldpwd(t_env *env, char *pwd)
{
	int		i;
	char	*pwd_ptr;

	pwd_ptr = NULL;
	i = -1;
	while (env->env_vars[++i]) //if have PWD
	{
		if (!ft_strncmp(env->env_vars[i], "PWD=", 4))
		{
			pwd_ptr = env->env_vars[i]; //to move to OLDPWD
			env->env_vars[i] = ft_strjoin("PWD=", pwd);
			free(pwd);
			printf("updated PWD\n");
			// free(pwd_ptr);
		}
	}
	if (!pwd_ptr) //if no PWD
		export_pwd(env, pwd);
	if (pwd_ptr)
		update_oldpwd(env, pwd_ptr);
	// free(pwd_ptr);
}

// void	update_pwd_oldpwd(t_env *env, char *pwd)
// {
// 	int		i;
// 	char	*pwd_ptr;
// 	char	**export;

// 	pwd_ptr = NULL;
// 	i = -1;
// 	while (env->env_vars[++i]) //if have PWD
// 	{
// 		if (!ft_strncmp(env->env_vars[i], "PWD=", 4))
// 		{
// 			pwd_ptr = env->env_vars[i]; //to move to OLDPWD
// 			env->env_vars[i] = ft_strjoin("PWD=", pwd);
// 			free(pwd);
// 			printf("updated PWD\n");
// 			free(pwd_ptr);
// 		}
// 	}
// 	if (!pwd_ptr) //if no PWD
// 	{
// 		printf("ft_cd: PWD not set\n");
// 		pwd_ptr = ft_strjoin("PWD=", pwd);
// 		export = (char **)malloc(2 * sizeof(char *)); //3 if pwd
// 		export[0] = pwd_ptr;
// 		export[1] = NULL;
// 		// export[1] = ft_strdup("OLDPWD=");
// 		// export[2] = NULL;
// 		ft_export(env, export);
// 		printf("ft_cd: exported PWD & OLDPWD (OLDPWD=[blank])\n");
// 		free_2d_arr(export);
// 	}
// 	// if (pwd_ptr)
// 	// 	update_oldpwd(env, pwd_ptr);
// 	// free(pwd_ptr);
// }

// [cd] [~] or [cd] [NULL]
void ft_cd(t_env *env, t_exe *exe, char **input)
{
	char	*home_path;
	char	*pwd;

	home_path = get_env_home(env);
	pwd = NULL;
	if (input[2])
	{
		printf("minishell: cd: too many arguments\n");
		return ;
	}
	if (input[1] == NULL)
	{
		if (home_path)
			exe->err_num = chdir(home_path);
		else
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
	}
	else
		exe->err_num = chdir(input[1]);
	if (exe->err_num == 0)
	{
		printf("ft_cd: chdir successful\n");
		if ((pwd = getcwd(NULL, 0)) == NULL)
			perror("failed to get current working directory\n");
		update_pwd_oldpwd(env, pwd);
	}
	else
		printf("minishell: cd: %s: No such file or directory\n", input[1]);
	free(home_path);
}

// if cd successfull chdir retunr 0 if not will return 1

//other cases:
//replace ~ with env->home_tilda if path ~/..... ??
//cd -