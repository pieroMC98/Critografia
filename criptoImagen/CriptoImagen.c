#include "./CritoImagen.h"

byte byteToBits(char B) {
	byte rt = (byte)calloc(8, sizeof(bit));
	for (int i = 8; i >= 0; --i) rt[i] = (char)((B >> i) & 1);
	return rt;
}

void printByte(byte B) {
	for (int i = 0; i < 8; i++) printf("%d", B[i]);
	printf("\n");
}

const char* fileType(const char* name) {
	regex_t expression;
	const char* regex = ".*\\.bmp$";
	if (regcomp(&expression, regex, REG_EXTENDED)) {
		fprintf(stderr, "Error al compilar regex\n");
		regfree(&expression);
		return NULL;
	}
	int reti = regexec(&expression, name, 0, NULL, 0);

	if (!reti) {
		regfree(&expression);
		return name;
	} else if (reti == REG_NOMATCH)
		fprintf(stderr, "Patron no coincide: %s\n", name);
	else {
		regerror(reti, &expression, (char*)name, sizeof(name));
		fprintf(stderr, "Formato '%s'\n", name);
	}

	regfree(&expression);
	return NULL;
}

FILE* exits(const char* name) {
	if (fileType(name) == NULL) {
		fprintf(stderr, "Formato incorrecto '%s'\n", name);
		return NULL;
	}

	FILE* fp = NULL;
	if ((fp = fopen(name, "rb")) != NULL) return fp;

	fclose(fp);
	free(fp);
	return NULL;
}

char* newFile() {
	char* file = (char*)malloc(BUFSIZ * sizeof(char));
	printf("Nombre de nuevo archivo\n");
	// scanf("%s", file);
	file = "hola.bpm";
	return file;
}

byte* encoding() {
	char* string = prepareString();
	unsigned tam = strlen(string);
	byte* rt = (byte*)calloc(tam, sizeof(byte));

	for (int i = 0; i < tam; i++)
		rt[i] = (byte)byteToBits(string[i]);
	
	free(string);
	return rt;
}

void prepararFichero(FILE* fp) {
	unsigned i;
	fseek(fp, 28, SEEK_SET);
	fread(&i, sizeof(char), 2, fp);
	printf("imagen de %d bits/pixel\n", i);
	fseek(fp, 10, SEEK_SET);
	fread(&i, sizeof(char), 4, fp);
	printf("direccion de inicio de imagen: %d\n", i);
}

char* prepareString() {
	char* rt = (char*)malloc(20);
	printf("cadena de texto:");
	scanf("%s", rt);
	return rt;
}

FILE* cpFile(FILE* out, FILE* in) {
	fseek(in, 0, SEEK_END);
	unsigned char i;
	int tam = ftell(in);
	int iter, count = 0;

	printf("cadena -> %s\n", *encoding());
	while ((iter = ftell(in)) < tam) {
		fread(&i, sizeof(char), 1, in);
		printf("%d -> 0X%X, DEC = %d\n", iter, i, i);
		// printByte(  byteToBits(i));
		if ((count++) == 60) break;
		// fwrite(i, rest, sizeof(char), out);
	}
	return out;
}
FILE* insertar(FILE* fp) {
	FILE* out_file = cpFile(fopen(newFile(), "wb"), fp);

	return out_file;
}

FILE* extraer(FILE* fp) { return NULL; }

FILE* option(const char* name) {
	int opt = 0;
	FILE* fp = exits(name);
	if (fp == NULL) return NULL;
	FILE* out;
	printf("insertar(0) o extraer(1) para \"%s\"\n", name);
	// scanf("%d", &opt);
	opt = 0;
	switch (opt) {
		case 0:
			out = insertar(fp);
			break;
		case 1:
			break;
		default:
			break;
	}
	return out;
}
