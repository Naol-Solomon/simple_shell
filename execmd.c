#include "main.h"
/**
 * execmd - Executes a command with the given arguments
 * @cmd_argv: The array of command arguments
 */
void execmd(char **cmd_argv)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *command_location = get_location(cmd_argv[0]);

		if (command_location == NULL)
		{
			fprintf(stderr, "Command not found: %s\n", cmd_argv[0]);
			exit(EXIT_FAILURE);
		}
		if (execve(command_location, cmd_argv, NULL) == -1)
		{
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
