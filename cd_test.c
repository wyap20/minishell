#include <unistd.h> // execve
#include <stdio.h> // perror
#include <string.h> // strerror
#include <errno.h> // errno
#include <dirent.h> // opendir(), readdir() & closedir()

int main() 
{
	char *buffer;
	int error_no; // 0 for success & -1 for error

	DIR *dir;
	struct dirent *dp;

	printf("%s\n",(getcwd(buffer,__INT_MAX__)));
	
	dir = opendir(".");
	while ((dp = readdir(dir)) != NULL) // for wildcard BONUS
		printf ("[%s]\n", dp->d_name);
	
	// error_no = chdir(".."); // move up 1 level aka go back
	// error_no = chdir("."); //changes the current working directory of the process to the current directory
	// error_no = chdir("test"); // if no path
	error_no = chdir("src"); // if there is path
	// error_no = chdir("src/parsing"); // if multi link path
	// error_no = chdir("/usr/local/bin"); // direct
	
	/* method A */
	if (chdir("src")) // valid path
		perror("");
	if (chdir("test")) // no valid path
		perror("");

	/* method B */
	if (error_no == -1) // if not scuessfull
		printf("%s\n",strerror(errno));
		// perror(""); // perror catches both Succes and Error & print it out...
	else if (error_no == 0)
		printf("%s\n",(getcwd(buffer,__INT_MAX__)));
		// perror(""); 
	
	closedir(dir);
	return 0;
}

/* #include <dirent.h>
need tp use in conjuntion with opendir() readdir() & closedir()? */