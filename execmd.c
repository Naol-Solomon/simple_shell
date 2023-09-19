#include "main.h"

void execmd(char **argv)
{
    char *finalCommand = NULL, *command = NULL;
    command = argv[0];
    
    finalCommand = get_location(command); 

    if (finalCommand != NULL)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork failed");
            return;
        }
        if (pid == 0){
           if (execve (finalCommand, argv, NULL) == -1){
            perror ("execute failed");
            exit (EXIT_FAILURE);
           }
        }
        else {
            int status;
            waitpid (pid, &status, 0);
           }
        }

    else {
        return;
    }
}
