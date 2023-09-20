#include "main.h"

/**
 * print_environ - Prints the current environment
 */
void print_environ()
{
    char **env = environ;
    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}