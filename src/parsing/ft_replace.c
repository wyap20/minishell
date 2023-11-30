/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 01:43:18 by atok              #+#    #+#             */
/*   Updated: 2023/11/30 01:43:18 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

char *ft_replace (char *str, char *key, char *val)
{
	int len = strlen(str)-strlen(key)+strlen(val);
	char *ns = malloc(sizeof(char) * (len + 1));
	
	ft_strcpy (ns, str);

	char *ptr = ft_strstr (ns, key);
	if (ptr)
	{
		//dst will be where the end of val is. src wiil be end of key. n will be wehre key/src end
		// moving the raminder to the back remainder=anyhong after key)
		ft_memmove (ptr+strlen(val), ptr+strlen(key), strlen(ptr+strlen(key))+1);
		ft_strncpy (ptr, val, strlen(val));
	}

	return (ns);
}

int main(void)
{
	// char arg[]= "atok";
	// char *$USER = arg;
	// char *$USER = "atok";
	// printf("hi%s\n", $USER);

	// char *intput = "echo $test 42";
	// char *$test = "42 kl is muy home";
	// char *$output = "echo 42 kl is muy home 42";

	// char *str = "echo me$USER";
	char *str = "echo me$USERme";
	// char *str = "echo me$USER me";
	// char *str = "echo me$USER test$USER";


	char *key = "$USER";
	// char *val = "tok";
	char *val = "usernameisatok";
	char *ns;

	ns = ft_replace(str,key,val);
	printf("%s\n",ns);
	free(ns);
	return(0);
}

// while loop input find $
// substr $... return it as char *key
// for val, use key to find val