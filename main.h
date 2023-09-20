#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
extern char **environ;

/*function prototype*/
void execmd(char **argv);
char *get_location(char *command);
void exit_shell();
void print_environ();

#endif