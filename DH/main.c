#include "./DH.h"
int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("parametros alfa y q\n");
		return EXIT_FAILURE;
	}

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	printf("argumentos alfa = %d y q = %d\n", a, b);
	if (run(a, b) == EXIT_FAILURE) return EXIT_FAILURE;
	return 0;
}
