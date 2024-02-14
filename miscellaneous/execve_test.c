
#include <unistd.h> // execve
#include <stdio.h> // perror

int main() 
{
	// char *args[] = {"/bin/ls","-lh", NULL};

	char *args[3];
	args[0] = "/bin/ls";
	args[1] = "-l";
	args[2] = NULL; //<< must have

	// execve(args[0], args, NULL); // path , 2d array format, NULL
	execve("/bin/ls", (char*[]){"anything", "-l", NULL}, NULL); // 1st arg cannot be NULL but can be anything
	perror("execve"); //<< perror usage
	return 1;
}