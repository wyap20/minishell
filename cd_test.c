#include <unistd.h> // execve
#include <stdio.h> // perror
#include <string.h> // strerror
#include <errno.h> // errno

int main() 
{
	char *buffer;
	int tmp;

	printf("%s\n",(getcwd(buffer,__INT_MAX__)));
	// chdir("..");
	chdir(".");
	// tmp = chdir("test"); // if no path
	// tmp = chdir("src"); // if there is path
	// tmp = chdir("src/parsing"); // if multi link path
	// tmp = chdir("/usr/local/bin"); // direct
	
	if (tmp != 0)
		printf("%s\n",strerror(errno));
		// perror("");
	else
		printf("%s\n",(getcwd(buffer,__INT_MAX__)));
		// perror(""); // perror catches Succes and Error....
	
	return 0;
}

/* #include <dirent.h>
need ot use in conjuntion with opendir() readdir() & closedir()? */