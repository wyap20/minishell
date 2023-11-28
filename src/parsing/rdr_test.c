#include <stdio.h>
#include <unistd.h>
#include <string.h> //test
#include "../../minishell.h"



size_t	rdrio(char *s)
{
	size_t i = 0;
	size_t j = 0;
	char *input;
	char *filename;
	char *op;
	
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
		{
			input = ft_substr(s, 0, i); //malloc
			j = i + 1;
			if (s[i] == '>')
				op = ">";
			else if (s[i] == '<')
				op = "<";
			if (s[i] == '>' && s[i + 1] == '>')
			{
				j = i + 2;
				op = ">>";
			}
			break;
		}
		i++;
	}
	i = ft_strlen(s) - 1;
	filename = ft_substr(s, j, i - j + 1);
	filename = ft_strtrim(filename, " "); //malloc
	input = ft_strtrim(input, " "); //malloc
	printf("input: %s\nfilename: %s\nop: %s\n", input, filename, op);
	return (0);
}

int main()
{
	char *s1, *s2, *s3;

	s1 = "asdfasdf > file1";
	s2 = "zxcvzxcv >> file1";
	s3 = "tr \'a\' \'d\' < file1|csac";

	rdrio(s1);
	rdrio(s2);
	rdrio(s3);
}