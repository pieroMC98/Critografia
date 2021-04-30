// Un pequeño ejemplo de como insertar bits de texto en bytes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char mensaje[256] = "Atacar";  // Texto del mensaje a insertar
unsigned char bytes[64];       // Cadena  de bytes donde queremos insertarlo

void main(void) {
	int i, j, k;
	char var1;
	char var2;
	int longi;
	int divi;

	// Vamos a rellenar aleatoriamente los bytes con valores entre 0 y 255. Aquí irían bytes de imagen
	for (i = 0; i < 64; i++) bytes[i] = rand() % 256;

	printf("Los bytes que se van a modificar son:\n\n ");
	for (i = 0; i < 64; i++) {
		printf("0x%02x ", (unsigned short)bytes[i]);
		if (((i + 1) % 8) == 0) printf("\n");
	}
	printf("\n\n");

	longi = strlen(mensaje);
	printf("El mensaje a incrustar es %s y tiene %d caracteres. Se requieren %d bytes\n", mensaje, longi,
	       longi * 8);

	// Para cada byte del mensaje usaremos 8 bytes de "imagen"
	k = 0;	// k indica en qué byte incrustamos el bit de más a la derecha
	for (i = 0; i < longi; i++) {
		var1 = mensaje[i];

		printf("\nEl caracter a incrustar es '%c' que en hexadecimal es 0x%02x y en binario es ", var1,
		       (unsigned short)var1);
		for (j = 0, divi = 128; j < 8; j++, divi = divi / 2) printf("%d ", (var1 & divi) / divi);
		printf("\n");

		printf("Los 8 bytes afectados quedaron como:\n");

		// Vamos a incrustar el j-ésimo bit del i-ésimo byte del mensaje en el k-ésimo byte
		for (j = 0; j < 8; j++) {
			var2 = var1 & 0x01;  // Nos quedamos con el bit de la derecha (0 ó 1);
			if (var2 == 0)
				bytes[k] = bytes[k] & 0xFE;  // Si el bit vale 0 hacemos AND con 0xFE
			else
				bytes[k] = bytes[k] | 0x1;  // Si el bit vale 0 hacemos OR con 0x01
			printf("0x%02x ", (unsigned short)bytes[k]);
			var1 = var1 / 2;  // Dividimos entre 2 para desplazar una posición a la derecha
			k++;		  // Para apuntar al siguiente byte de bytes
		}
		printf("\n");
	}
}
