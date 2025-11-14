#include <stdio.h>

int main(void) {
	int i, s;

	printf("Output without strength reduction:\n");
	for (i = 1; i <= 10; i++) {
		s = i * 2;
		printf("%d ", s);
	}
	printf("\n");
	return 0;
}