#include "cripto.h"
#include "header.h"
int main(int argc, char *argv[]) {
	if (argc <= 2) {
		printf("parmatros para '%s' opt a b p\n", argv[0]);
		return 1;
	}

	int opt = atoi(argv[1]);
	if (opt < 1 || opt > 4) {
		printf("opt 1 -> modulo \n\
			2 -> mcd \n\
			3 -> cribaEratostenes \n\
			4 -> factorizacion\n");
		return 1;
	}
	li j;

	int a = atol(argv[2]);
	int b = atol(argv[3]);
	int p = atol(argv[4]);
	li *sol= option(opt, a, b, p, &j);
	if (sol == NULL) return 1;
	print(sol, j);
	free(sol);
	return 0;
}
