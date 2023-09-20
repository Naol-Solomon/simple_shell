#include "main.h"

/**
 * main - Entry point of the shell program
 * @ac: The number of command-line arguments
 * @argv: An array of command-line arguments
 *
 * Return: 0 on success, -1 on failure
 */
int main(int ac, char **cmd_argv)
{
	char *prompt = ":) ";
	char *fullCommand = NULL, *copyCommand = NULL;
	char *token;
	size_t i = 0;
	size_t num_token = 0;
	size_t n = 0;
	ssize_t read;
	char *delim = " \n";
	(void)ac;

	while (1)
	{	if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, strlen(prompt));
		read = getline(&fullCommand, &n, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "Exiting shell ...\n", 18);
			break;
		}
		
		fullCommand[strcspn(fullCommand, "\n")] = '\0';
		if (read <= 1)
		{
			continue;
		}
		copyCommand = malloc(sizeof(char) * (read + 1));
		if (copyCommand == NULL)
		{
			perror("Memory allocation failed");
			return (-1);
		}
		strcpy(copyCommand, fullCommand);
		token = strtok(fullCommand, delim);
		while (token != NULL)
		{
			num_token++;
			token = strtok(NULL, delim);
		}
		num_token++;
		cmd_argv = malloc(sizeof(char *) * (num_token + 1));
		token = strtok(copyCommand, delim);
		for (i = 0; token != NULL; i++)
		{
			cmd_argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(cmd_argv[i], token);
			token = strtok(NULL, delim);
		}
		cmd_argv[i] = NULL;
		if (strcmp(cmd_argv[0], "exit") == 0)
        {
            exit_shell();
        }
        else if (strcmp(cmd_argv[0], "env") == 0)
        {
            print_environ();
            continue;
        }
		execmd(cmd_argv);
		for (i = 0; cmd_argv[i] != NULL; i++)
		{
			free(cmd_argv[i]);
		}
		free(cmd_argv);
		free(copyCommand);
	}
	free(fullCommand);
	return (0);
}
