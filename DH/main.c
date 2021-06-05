#include <stdlib.h>

#include "./DH.h"
int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("parametros a y b\n");
		return EXIT_FAILURE;
	}

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	printf("argumentos a = %d y b = %d\n", a, b);
	if (run(a, b) == EXIT_FAILURE) return EXIT_FAILURE;
	return 0;
}
