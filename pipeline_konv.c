//#include <iostream>
#include <string.h>
#include <stdio.h>
//#include <vector>
#include <sys/types.h>
#include <unistd.h>
//using namespace std;

//This program will do three different commands ls, wc, then less.
int	main()
{
	pid_t	pid = 0;
	int	cmd=3, i;
  //One less pipe than command is required.
	int fd[cmd-1][2];
  //The pipes are created in a for loop.
	for(int i=0; i<(cmd-1); i++)
	{
		if(pipe(fd[i])==-1)
			printf("Error");
	}
  //The commands are put in c.
	char *c[][3] = {{"ls", "-la", NULL}, {"grep", "-p", NULL}, {"cat", "-e", NULL}};

	for (i = 0; i < cmd-1; i ++)
	{
		pid = fork();
		if (pid == -1)
			printf("Error\n");
		if (pid == 0)
		{
			if (i != 0)
			{
				// read from previous fd
				close(fd[i-1][1]);
				dup2(fd[i-1][0], STDIN_FILENO);
				close(fd[i-1][0]);
			}
			// write to current fd
			close(fd[i][0]);
			dup2(fd[i][1], STDOUT_FILENO);
			close(fd[i][1]);
			temp[0] = c[i];
			temp[1] = NULL;
			execvp(c[i], temp);
			//exit(0);
		}
    	else
		{
			if (i != 0)
			{
				// close unnecessary fds in parent
				close(fd[i-1][0]);
				close(fd[i-1][1]);
			}
		}
	}
	// the last command i.e. less here
	if(i > 0)
	{
		close(fd[i-1][1]);
		dup2(fd[i-1][0], STDIN_FILENO);
		close(fd[i-1][0]);
	}
	temp[0] = c[i];
	temp[1] = NULL;
	execvp(c[i], temp);
	return 0;
}
