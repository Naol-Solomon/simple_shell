#include "main.h"

int main(int ac, char **argv)
{
    char *prompt = "$ ";
    char *fullCommand = NULL, *copyCommand = NULL;
    char *token;
    size_t i;
    size_t num_token = 0;
    size_t n = 0;
    ssize_t read;
    char *delim = " \n";

    (void) ac;

    while (1)
    {
        printf("%s", prompt);
        read = getline(&fullCommand, &n, stdin);

        if (read == -1)
        {
            printf("Exiting shell ...\n");
            return (-1);
        }
        /* continue to display prompt while pressing enter key without inserting commands */
        if (read <= 1){
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
       argv = malloc(sizeof(char*) * (num_token + 1));

        token = strtok(copyCommand, delim);
        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;
        execmd(argv);

        for (i = 0; i < num_token - 1; i++)
        {
            free(argv[i]);
        } 
        free(argv);
    }
    
    free(copyCommand);
    free(fullCommand);
    return (0);
}