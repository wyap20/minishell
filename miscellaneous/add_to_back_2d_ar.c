#include <unistd.h> // execve
#include <stdio.h> // perror
#include <stdlib.h>

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

int main() {
	char *array[3];

	array[0] = "one";
	array[1] = "two";
	array[2] = NULL;

	int i = 0;
	while (array[i] != 0x00)
		printf("%s\n", array[i++]);

	
	// char *new[4];
	char **new = malloc(sizeof(char**) * 4);
	i = 0;
	while (array[i] != 0x00)
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = "three";
	i++;
	new[i] = NULL;

	// free(array);
	// here no need becase the array did not use malloc
	
	i = 0;
	while (new[i] != 0x00)
		printf("%s\n", new[i++]);

	// while (new[i] != 0x00)
	// 	free(new[i++]);
	free(new);
	return 0;
}
