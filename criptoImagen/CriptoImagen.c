#include <stdio.h>

#include "./CritoImagen.h"

byte byteToInt(char B) {
	byte rt = calloc(8, sizeof(byte));
	for (int i = 8; i >= 0; --i) rt[i] = (char)((B >> i) & 1);

	return rt;
}

void printByte(byte B) {
	for (int i = 0; i < 8; i++) printf("%c", B[i]);
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

FILE* cpFile(FILE* out, FILE* in) {
	fseek(in, 0, SEEK_END);
	unsigned lecture = 255;
	char i[lecture];
	int tam = ftell(in);
	rewind(in);
	fseek(in, 24, SEEK_CUR);
	unsigned rest = 1;

	while (fseek(in, 0, SEEK_SET) < tam) {
		//fread(i, sizeof(char), 1, in);
		printf("leo(%uB):\n", rest);
		//printf("%d\n",(int) i);
		// fwrite(i, rest, sizeof(char), out);
		rest += lecture;
		if (rest < tam) continue;
		rest %= lecture;
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
