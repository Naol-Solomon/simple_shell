#include "main.h"

/**
 * execmd - Executes a command with the given arguments
 * @cmd_argv: The array of command arguments
 */
void execmd(char **cmd_argv)
{
	int i = 0;

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
			char error_message[100];

			sprintf(error_message, "Command not found: %s\n", cmd_argv[0]);
			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(EXIT_FAILURE);
		}
		if (execve(command_location, cmd_argv, environ) == -1)
		{
			free(command_location);
			for (i = 0; cmd_argv[i] != NULL; i++)
			{
				free(cmd_argv[i]);
			}
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
