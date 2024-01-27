/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_cmdv2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:38:57 by atok              #+#    #+#             */
/*   Updated: 2024/01/27 13:23:11 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != 0x00 || s2[i] != 0x00))
	{
		if ((s1[i] > s2[i]) || (s1[i] < s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != 0x00)
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*tmp;

	i = ft_strlen(s1);
	tmp = (char *)malloc((i + 1) * sizeof(char));
	if (!tmp)
		return (0);
	i = 0;
	while (s1[i] != 0x00)
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = 0x00;
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s || len == 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (s[start] && i < len)
	{
		if (s[start] == 0x00)
			break ;
		sub[i++] = s[start++];
	}
	sub[i] = 0x00;
	return (sub);
}

int	word_count(const char *s, char c)
{
	size_t	count;
	size_t	trigger;

	count = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			trigger++;
			count++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (count);
}

char	*word_dup(const char *s1, int start, int end)
{
	int		i;
	char	*tmp;

	if (!s1)
		return (0);
	tmp = (char *)malloc((end - start + 1) * sizeof(char));
	i = 0;
	if (!tmp)
		return (0);
	while (start < end)
		tmp[i++] = s1[start++];
	tmp[i] = 0x00;
	return (tmp);
}

size_t	ft_whileloop(const char	*s, char c, char	**split)
{
	size_t	i;
	size_t	j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && k == -1)
			k = i;
		else if ((s[i] == c || i == ft_strlen(s)) && k >= 0)
		{
			split[j++] = word_dup(s, k, i);
			k = -1;
		}
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	char	**split;

	if (!s)
		return (0);
	split = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	j = ft_whileloop(s, c, split);
	split[j] = 0x00;
	return (split);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

int	jstrlen(char const *str)
{
	int	len;

	len = 0;
	while (str[len] != 0x00)
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ss;
	int		dl;
	int		sl;

	if (s1 == 0x00 || s2 == 0x00)
		return (0);
	ss = (char *)malloc((jstrlen(s1) + jstrlen(s2) + 1) * sizeof(char));
	if (ss == NULL)
		return (NULL);
	dl = 0;
	while (s1[dl] != 0x00)
	{
		ss[dl] = s1[dl];
		dl++;
	}
	sl = 0;
	while (s2[sl] != 0x00)
	{
		ss[dl] = s2[sl];
		sl++;
		dl++;
	}
	ss[dl] = 0x00;
	return (ss);
}

char *ft_get_cmd_path(char **path, char*cmd)
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
	return(cmd);
}

int	main(int ac, char **av, char **envp)
{
	char *tmp;
	char **path;
	char *buffer;
	char *output;
	int i;

	i = 0;
	while (envp[i] != 0x00)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			// printf("%s\n", envp[i]);
		tmp = ft_substr(envp[i], 5, (int)ft_strlen(envp[i]) - 5);
		i++;
	}
	// printf("%s\n", tmp);
	path = ft_split(tmp,':');
	// i = 0;
	// while(path[i] != 0x00)
	// 	printf("%s\n", path[i++]);

	// ft_get_cmd_path(path,cmd);
//--------------------------------------

	char *result;
	char cmd[] = "z"; // << if no valid cmd path will get erro "freeing address wihch is not allocated"
	result = ft_get_cmd_path(path,cmd);
	printf("%s\n",result);

	// free 2D path, 1D tmp & 1D result
	i = 0;
	while (path[i] != 0x00)
		free(path[i++]);
	free(path);
	free(tmp);
	free(result);
	
	return(0);
}
