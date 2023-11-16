/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:57:03 by atok              #+#    #+#             */
/*   Updated: 2022/10/19 10:57:03 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* int main (void)
{
	char s1[] = "front";
	char s2[] = "back";
	char *ss = ft_strjoin(s1,s2);
	
//	printf(":%s:\n",ft_strjoin(s1,s2));
	printf(":%s:\n",ss);

	free(ss);

	return (0);
} */

/* malloc s1 & s2 +1
then proceed with strcat
without malloc will seg falt 
*/