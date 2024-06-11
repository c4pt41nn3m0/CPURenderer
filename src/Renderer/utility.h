#ifndef UTILITY_H
#define UTILITY_H

void int_swap(int* a, int* b)
{
	if (a == NULL || b == NULL)
		return;

	int temp = *a;
	*a = *b;
	*b = temp;
}

#endif