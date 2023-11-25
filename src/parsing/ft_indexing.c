/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:10:48 by atok              #+#    #+#             */
/*   Updated: 2023/11/26 01:10:48 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_len(char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
		i++;
	
	return (i);
}


int *ft_setup(char *str)
{
	int len;

	len = ft_len(str);
	printf("len - %d\n",len);
	int *id;

	id = (int*)malloc(sizeof(int) * (len + 1));
	id[len] = -1;
	int i;
	i = 0;
	while (id[i] != -1)
	{
		id[i] = 0;
		i++;
	}
	return (id);
}

int *ft_index_quote(int *out, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == '\'')
		{
			out[i++] = 1;
			while(str[i] != '\'')
				out[i++] = 1;
			out[i] = 1;
		}	
		else if(str[i] == '\"')
		{
			out[i++] = 2;
			while(str[i] != '\"')
				out[i++] = 2;
			out[i] = 2;
		}	
		i++;
	}
	return (out);

}
int *ft_index_uniquote(int *out, char *str)
{
	int i;
	char c;

	i = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			out[i] = 1;
			i++;
			while(str[i] != c)
				out[i++] = 1;
			out[i] = 1;
			c = 0x00;
		}	
		i++;
	}
	return (out);
}

int *ft_index_left_arrow(int *out, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == '<' && str[i + 1] == '<')
		{
			if(out[i] == 0)
				out[i] = 6;
			i++;
			if(out[i] == 0)
				out[i] = 6;
			i++;
		}
		if(str[i] == '<' && str[i + 1] != '<')
		{
			if(out[i] == 0)
				out[i] = 4;
		}
		i++;
	}
	return (out);
}

int *ft_index_right_arrow(int *out, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == '>' && str[i + 1] == '>')
		{
			if(out[i] == 0)
				out[i] = 5;
			i++;
			if(out[i] == 0)
				out[i] = 5;
			i++;
		}
		if(str[i] == '>' && str[i + 1] != '>')
		{
			if(out[i] == 0)
				out[i] = 3;
		}
		i++;
	}
	return (out);

}

int *ft_index_pipe(int *out, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == '|') 
		{
			if(out[i] == 0)
				out[i] = 7;
		}
		i++;
	}
	return (out);
}

int *ft_index_space(int *out, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0x00)
	{
		if(str[i] == ' ') 
		{
			if(out[i] == 0)
				out[i] = 8;
		}
		i++;
	}
	return (out);
}

int *ft_index_others(int *out)
{
	int i;

	i = 0;
	while (out[i] != -1)
	{
		if(out[i] == 0) 
		{
			out[i] = 1;
		}
		i++;
	}
	return (out);
}

int *ft_saperate(int *out, char *str)
{
	int i;

	i = 0;
	while (out[i] != -1)
	{
		if (out[i] == 8)
			i++;
		write(1, &str[i], 1);
		if (out[i] != out[i + 1])
			write(1, "\n", 1);
		i++;
	}
	return (out);
}

int main (void)
{
	// char str[] = "ls | grep Mov | wc -c";
	// char str[] = "ls<< \'| grep <>\"Mov \' | <wc> \"\'\" \'test\'\'ting\'-c";
	// char str[] = "ls<< \'| grep <>\"Mov \' | <wc> \"\'\" \'test\'\"ting\"-c";
	// char str[] = "echo 'test'\"ting\"";
	// char str[] = "echo \"test\"\"ting\"";
	char str[] = "echo \"test\"\"ting\"-c";
	int *out;
	
	out = ft_setup(str);

	// out = ft_index_quote(out,str);
	out = ft_index_uniquote(out,str);
	
	out = ft_index_left_arrow(out,str);
	out = ft_index_right_arrow(out,str);
	out = ft_index_pipe(out,str);
	out = ft_index_space(out,str);
	out = ft_index_others(out);
	out = ft_saperate(out,str);

	// printf("%c\n",str[20]);
	int i = 0;
	while(out[i] != -1)
	// while(i < 22)
	{
		printf("%d,",out[i]);
		i++;
	}
	printf("%d",out[i]);
	printf("\n");
	free(out);
	return (0);
}