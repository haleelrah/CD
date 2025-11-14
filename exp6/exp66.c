#include <stdio.h>

#define MAX 6

int main(void) {
	int n = 1, s = 0;

	printf("Output without Code movement technique:\n");
	while (n <= MAX - 1) {
		s = s + n;
		n++;
	}
	printf("Sum of First 5 Numbers: %d\n", s);
	return 0;
}