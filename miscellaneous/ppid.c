#include <stdio.h>
#include <unistd.h>

int	main()
{
	int pid = getpid();
	int ppid = getppid();
	printf("pid: %d\n", pid);
	printf("ppid: %d\n", ppid);
}