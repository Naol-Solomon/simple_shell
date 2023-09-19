#include "main.h"

char *get_location(char *command)
{
    char *path, *pathCopy, *pathToken, *filePath;
    int commandLength, directoryLength;
    struct stat buff;

    path = getenv("PATH");
    if(path){
        pathCopy = strdup(path);
        commandLength = strlen(command);
        pathToken = strtok(pathCopy, ":");

        while (pathToken != NULL){
            directoryLength = strlen(pathToken);
            filePath = malloc(commandLength + directoryLength + 2 + 1);

            strcpy (filePath, pathToken);
            strcat (filePath, "/");
            strcat (filePath, command);

            if (stat (filePath, &buff) == 0) {

                free (pathCopy);
                return(filePath);
            }
            else 
            {
                free(filePath);
                pathToken = strtok (NULL, ":");
            }

        }
            
        free (pathCopy);

        if (stat (command, &buff) == 0)
            return (command);

        return (NULL);
    }  
  
    return (NULL);
}

