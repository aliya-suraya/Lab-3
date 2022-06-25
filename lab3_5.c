#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define waiting 50

int main (void) {
	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	if(pid>0)
	{
		close(0);
		close(fd[1]);
		dup(fd[0]);

		int prime, flag=0;
		read(fd[0], &prime, sizeof(prime));
		printf("Checking prime number..\n");
		wait (NULL);

		for (int i=2; i<prime/2; i++)
		{
			if(prime%i ==0){
			printf("%d is not a prime number\n", prime);
			flag=1;
			break;
			}
		}

		if(flag=0){
			printf("%d is a prime number\n", prime);
		}

		printf("Press ctrl c to terminate program\n");
		sleep(waiting);
	}

	else if (pid==0)
	{
		int number;
		printf("Enter a number: ");
		scanf("%d", &number);
		write(fd[1], &number, sizeof(number));
		close(1);
		close(fd[0]);
		dup(fd[1]);
		exit(EXIT_SUCCESS);
	}

	return EXIT_SUCCESS;
}

