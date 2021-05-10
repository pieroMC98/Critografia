#include "../header.h"
typedef char *byte;
typedef char bit;
const char *fileType(const char *);
FILE *exits(const char *);
FILE *option(const char *);
FILE *insertar(FILE *);
FILE *extraer(FILE *);
byte byteToBits(char);
void prepararFichero(FILE *);
char *prepareString();
void printByte(byte);
