#include "main.h"

/**
 * main - accept user name and age
 * return: zero on successful of the code
 */

int main(void) 
{
       char name[100];
       int age;
       
       printf("Enter your name: ");
       scanf("%s", name);
       printf("Enter your age: ");
       scanf("%d", &age);
       if (age <= 15)
	       printf("Hi %s! you are %d years old, so are to young to be a Soldier!", name, age);
       else if (age <= 30)
	       printf("Hi %s! you are %d years old so you can be a Soldier!", name, age);
       else 
	       printf("Hi %s! you are %d years old so to old to be a Soldier!", name, age);
       return 0;
}
