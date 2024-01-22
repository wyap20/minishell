#include "../../minishell.h"

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
