#include "cripto.h"
int main(int argc, char *argv[]) {
	srand(time(NULL));
	if (argc <= 2) {
		printf("parmatros para '%s' a b p\n", argv[0]);
		return 1;
	}

	li j;
	int a = atol(argv[1]);
	int b = atol(argv[2]);
	int p = atol(argv[3]);
	li *sol = option(a, b, p, &j);
	// print(sol, j);
	// gordon(a, 20);
	if (sol == NULL) {
		free(sol);
		fprintf(stderr, "Error en las operaciones");
		return 1;
	}
	free(sol);
	return 0;
}
