#include "cripto.h"
#include "header.h"
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
	if (sol == NULL) return 1;
	print(sol, j);
	free(sol);
	return 0;
}
