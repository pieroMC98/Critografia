#include "./CritoImagen.h"

int main(int argc, char *argv[]) {
	char *test = (char *)malloc(sizeof(char));
	if (argc > 1) {
		int l = strlen(argv[1]) + 1;
		test = (char *)realloc(test, l * sizeof(char));
		strcpy(test, argv[1]);
	} else {
		printf("archivo bpm como parametro\n");
		return 1;
	}

	if(option(test)) return 1;

	free(test);
	return 0;
}
