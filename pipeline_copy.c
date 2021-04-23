/* 
	pipeline.c : create the pipeline 

		who | cut -f1 -d' ' | uniq

*/

#include "utils/libft/libft.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <mach/error.h>



typedef struct cmnd
{
	char	**arr;
	int		pipe;
	struct cmnd	*next;
}				cmnd;

int main (int argc, char **argv) 
{
	t_list	*list;
	cmnd 	*com;

	com = NULL;
	com = (cmnd *)ft_calloc(sizeof(cmnd), 1);
	com->arr = (char **)ft_calloc(sizeof(char *), 3);
	com->arr[0] = ft_strdup("/bin/ls");
	com->arr[1] = ft_strdup("-la");
	com->arr[2] = NULL;
	com->pipe = 1;
	ft_lstadd_back(&list, ft_lstnew(com));
	printf("com[%d].arr[0] = %s\n", 0, com->arr[0]);
	printf("com[%d].arr[1] = %s\n", 0, com->arr[1]);
	printf("com[%d].arr[2] = %s\n", 0, com->arr[2]);
	printf("com[%d].pipe = %d\n", 0, com->pipe);
	com = com->next;

	com = (cmnd *)ft_calloc(sizeof(cmnd), 1);
	com->arr = (char **)ft_calloc(sizeof(char *), 3);
	com->arr[0] = ft_strdup("/usr/bin/grep");
	com->arr[1] = ft_strdup("a");
	com->arr[2] = NULL;
	com->pipe = 1;
	ft_lstadd_back(&list, ft_lstnew(com));
	printf("com[%d].arr[0] = %s\n", 1, com->arr[0]);
	printf("com[%d].arr[1] = %s\n", 1, com->arr[1]);
	printf("com[%d].arr[2] = %s\n", 1, com->arr[2]);
	printf("com[%d].pipe = %d\n", 1, com->pipe);
	com = com->next;

	com = (cmnd *)ft_calloc(sizeof(cmnd), 1);
	com->arr = (char **)ft_calloc(sizeof(char *), 3);
	com->arr[0] = ft_strdup("/bin/cat");
	com->arr[1] = ft_strdup("-e");
	com->arr[2] = NULL;
	ft_lstadd_back(&list, ft_lstnew(com));
	printf("com[%d].arr[0] = %s\n", 2, com->arr[0]);
	printf("com[%d].arr[1] = %s\n", 2, com->arr[1]);
	printf("com[%d].arr[2] = %s\n", 2, com->arr[2]);
	printf("com[%d].pipe = %d\n", 2, com->pipe);
	
	int	cms = ft_lstsize(list);
	int	pps = 0;
	int j = 0;
	t_list *tmp;
	tmp = list;

	while (tmp) {
		if (tmp->content)
	}
	


	int pfd1 [2], pfd2 [2];
	pid_t pid1, pid2, pid3;

	if (pipe (pfd1) == -1)
	   perror ("pipe");

	pid1 = fork ();

	if (pid1 == 0) {
		// first child, will become "who"
		printf(" pid1 %d\n", pid1);
		if (dup2 (pfd1 [1], STDOUT_FILENO) == -1)
			perror ("dup2");
		if (close (pfd1 [0]) == -1)
			perror ("close");
		if (close (pfd1 [1]) == -1)
			perror ("close");
		execlp ("who", "who", (char *) NULL);
		perror ("execlp");
	}

	/* parent process */
	if (pipe (pfd2) == -1)
	   perror ("pipe");

			pid2 = fork ();

			if (pid2 == 0) {
			// second child, who will become "cut"
			if (dup2 (pfd1 [0], STDIN_FILENO) == -1)
				perror ("dup2");
			if (dup2 (pfd2 [1], STDOUT_FILENO) == -1)
				perror ("dup2");
			if (close (pfd1 [0]) == -1)
				perror ("close");
			if (close (pfd1 [1]) == -1)
				perror ("close");
			if (close (pfd2 [0]) == -1)
				perror ("close");
			if (close (pfd2 [1]) == -1)
				perror ("close");
			execlp ("cut", "cut", "-f1", "-d ", (char *) NULL);
			perror ("execlp");
		}

	/* parent process */

	if (close (pfd1 [0]) == -1)
		perror ("close");
	if (close (pfd1 [1]) == -1)
		perror ("close");

				pid3 = fork ();

				if (pid3 == 0) {
					// third child, who will become "uniq"
					if (dup2 (pfd2 [0], STDIN_FILENO) == -1)
						perror ("dup2");
					if (close (pfd2 [0]) == -1)
						perror ("close");
					if (close (pfd2 [1]) == -1)
						perror ("close");
					execlp ("uniq", "uniq", (char *) NULL);
					perror ("execlp");
				}

	/* parent process */

	if (close (pfd2 [0]) == -1)
		perror ("close");
	if (close (pfd2 [1]) == -1)
		perror ("close");

	if (waitpid (pid1, NULL, 0) == -1)
		 perror ("waitpid");

	if (waitpid (pid2, NULL, 0) == -1)
		 perror ("waitpid");

	if (waitpid (pid3, NULL, 0) == -1)
		 perror ("waitpid");
}
