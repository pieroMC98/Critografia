#include "./CritoImagen.h"

FILE* cpFile(FILE* out, FILE* in) {
	unsigned char i, aux;
	int wfpointer = prepararFichero(in);
	fseek(in, 0, SEEK_END);
	int tam = ftell(in);
	rewind(in);

	int iter, count = 0, contador = 0, tamString;
	char* string = prepareString();

	byte insert = byteToBynary(encoding(&tamString, string), string);
	free(string);
	printf("bits a insertar :");
	printByte(insert);

	while ((iter = ftell(in)) < tam) {
		fread(&i, sizeof(char), 1, in);
		aux = i;
		if (iter >= wfpointer && count < tamString) printf("%ld -> leo = %c\n", ftell(in) - 1, i);
		if (iter >= wfpointer)
			if (count < tamString) i |= insert[count++];
		fwrite(&i, sizeof(char), 1, out);
	}
	free(insert);
	return out;
}

FILE* insertar(FILE* fp) {
	FILE* out_file = cpFile(fopen(newFile(), "wb"), fp);

	return out_file;
}

FILE* extraer(FILE* fp) {
	int fin, count = 0;
	char i;
	char* rt = NULL;
	printf("inserte longitud de la cadena a extraer");
	scanf("%d", &fin);
	fin *= 8;
	rt = (byte)malloc(fin * sizeof(bit));
	fseek(fp, prepararFichero(fp), SEEK_SET);
	while ((fin--) > 0) {
		fread(&i, sizeof(bit), 1, fp);
		printByte(byteToBits(i));
		// rt[count++] = i & 0x01;
		rt[count++] = i & 0x01;
		printf("%ld -> leo %d de %d\n", ftell(fp), i, rt[count - 1]);
	}
	printf("%s\n", bitToChar(rt, 1));
	return NULL;
}
FILE* option(const char* name) {
	int opt = 0;
	FILE* fp = exits(name);
	if (fp == NULL) return NULL;
	FILE* out;
	printf("insertar(0) o extraer(1) para \"%s\"\n", name);
	scanf("%d", &opt);
	// opt = 0;
	switch (opt) {
		case 0:
			out = insertar(fp);
			break;
		case 1:
			out = extraer(fp);
			break;
		default:
			break;
	}
	fclose(fp);
	return out;
}

byte byteToBits(char B) {
	byte rt = (byte)calloc(8, sizeof(bit));
	for (int i = 8; i >= 0; --i) rt[i] = (char)((B >> i) & 0x01);
	return rt;
}

char* bitToChar(byte b, int length) {
	printByte(b);
	printf("cadena es =>%s\n", b);
	char* rt = (char*)malloc(length * sizeof(char));
	int l = (int)strtol(b, NULL, 2);
	printf("%X\n", l);
	//	int j = 0;
	length *= 8;
	for (int i = 0; i < length; i++) {
	}
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
	printf("Nombre de nuevo archivo(sin .bmp)\n");
	scanf("%s", file);
	strcat(file, ".bmp");
	return file;
}

byte* encoding(int* cad, char* string) {
	unsigned tam = strlen(string);
	byte* rt = (byte*)calloc(tam, sizeof(byte));

	printf("%s, %d\n", string, tam);
	for (int i = 0; i < tam; i++) rt[i] = (byte)byteToBits(string[i]);

	*cad = tam * 8;

	return rt;
}

char* prepareString() {
	char* rt = (char*)malloc(20);
	printf("cadena de texto:");
	scanf("%s", rt);
	return rt;
}

char* byteToBynary(byte* B, char* string) {
	char* rt = malloc(strlen(string));

	int iter = 0;
	for (int i = 0; i < strlen(string); i++)
		for (int j = 0; j < 8; j++) rt[iter++] = B[i][j];

	return rt;
}

unsigned prepararFichero(FILE* fp) {
	unsigned i;

	fseek(fp, 28, SEEK_SET);
	fread(&i, sizeof(char), 2, fp);
	printf("imagen de %d bits/pixel\n", i);

	fseek(fp, 10, SEEK_SET);
	fread(&i, sizeof(char), 4, fp);
	printf("direccion de inicio de imagen: %d\n", i);

	return i;
}
