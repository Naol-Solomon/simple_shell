#include <stdio.h>

/**
 * swapping - swaps two integer numbers
 * @a: pointer to integer parameter
 * @b: pointer to integer parameter
 * Return: void
 */
void swapping(int *a, int *b)
{
	int temp = *a;

	*a = *b;
	*b = temp;
}

/**
 * main - checks swapping function
 * Return: 0 on success
 */
int main(void)
{
	int x = 5;
	int y = 3;

	swapping(&x, &y);
	printf("%d\n%d\n", x, y);
	return (0);
}
