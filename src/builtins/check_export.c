#include "../../minishell.h"

/*
* executes when first character is alphabet or underscore
* validate remaining characters of variable to be alphanumeric or underscore
* if no '=', or remaining characters is invalid, return space
* otherwise return str as it is
*/
char	*check_remain_char1(char *str)
{
	char	**split;
	char	*buf;
	int		j;

	if (!ft_strchr(str, '='))
		return (" ");
	split = ft_split(str, '='); //split before first equal sign check if the rest is alphanumeric
	buf = split[0];
	if (buf)
	{
		j = 1;
		while (buf[j])
		{
			if (!ft_isalnum(buf[j]) && buf[j] != '_') //if remaining char is not alnum or underscore
			{
				printf("mark B: minishell -> export: invalid format: %s\n", buf);
				free_2d_arr(split);
				return (" ");
			}
			j++;
		}
	}
	free_2d_arr(split);
	return (str);
}

/*
* executes when first character of the key is not an alphabet
* obtain variable name to be included in error message
* set the string to one space, to be ignored later
*/
char	*check_remain_char2(char *str)
{
	char	**split;
	char	*buf;

	split = NULL;
	if (ft_strchr(str, '='))
	{
		split = ft_split(str, '=');
		buf = split[0];
	}
	else
		buf = str;
	printf("mark A: minishell -> export: invalid format: %s\n", buf);
	free_2d_arr(split);
	return (" ");
}

/*returns a 2d array containing valid variable to update*/
char **valid_vars(char **add, int size)
{
	char	**updated;
	int		i;
	int		j;

	i = 0;
	j = 0;
	updated = (char **)malloc((size + 1) * sizeof(char *));
	if (!updated)
		printf("export error: failed to update valid variables\n");
	while (add[i])
	{
		if (ft_strcmp(add[i], " "))
		{
			updated[j] = ft_strdup(add[i]);
			free(add[i]);
			j++;
		}
		i++;
	}
	updated[j] = NULL;
	return (updated);
}

/*
* skips string that has space to get the count of valid key/value pairs
* to malloc the right size in updated 2D array with valid key/value pair
* used in check_export()
*/
int	new_arr_size(char **add)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (add[i])
	{
		if (add[i][0] == ' ')
		{
			i++;
			j++;
		}
		i++;
	}
	printf("i:%d\nj: %d\n", i,j);
	return (i - j);
}

/*validate eligible new key/value to be added in the environment*/
char **check_export(char **add)
{
	char	**updated;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (add[i])
	{
		if (ft_isalpha(add[i][0]) || add[i][0] == '_') //if first char is alpha or underscore
			add[i] = check_remain_char1(add[i]);
		else if (!ft_isalpha(add[i][0])) //if first char is not alpha
			add[i] = check_remain_char2(add[i]);
		i++;
	}
	// printf("export: after checking\n");
	// i = 0;
	// while (add[i])
	// {
	// 	printf("%d: %s\n", i, add[i]);
	// 	i++;
	// }
	size = new_arr_size(add);
	// printf("new arr size:%d\n", size);
	updated = valid_vars(add, size);
	free(add);
	printf("export: updated (new variables to add)\n");
	i = 0;
	while(updated[i])
		printf("\t%s\n", updated[i++]);
	return (updated);
}