#include "main.h"

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
        /* Child process */
        char *command_location = get_location(cmd_argv[0]);
        if (command_location == NULL) {
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
        /* Parent process */
        waitpid(child_pid, &status, 0);
    }
}

int main(int ac, char **cmd_argv)
{
    char *prompt = ":) ";
    char *fullCommand = NULL, *copyCommand = NULL;
    char *token;
    size_t i;
    size_t num_token = 0;
    size_t n = 0;
    ssize_t read;
    char *delim = " \n";
    (void)ac;

    while (1)
    {
        printf("%s", prompt);
        read = getline(&fullCommand, &n, stdin);

        if (read == -1)
        {
            printf("Exiting shell ...\n");
            break;
	    }
        fullCommand[strcspn(fullCommand, "\n")] = '\0';

        if (read <= 1)
        {
            continue;
        }

        copyCommand = malloc(sizeof(char) * read);

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
        execmd(cmd_argv);

        for (i = 0; i < num_token; i++)
        {
            free(cmd_argv[i]);
        }
        free(cmd_argv);
    }

    free(copyCommand);
    free(fullCommand);
    return (0);
}
