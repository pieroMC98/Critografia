#include "../header.h"
typedef char *byte;
typedef char bit;
const char *fileType(const char *);
FILE *exits(const char *);
FILE *cpFile(FILE *, FILE *);
char *newFile();
char *bitToChar(byte, int);
int option(const char *);
FILE *insertar(FILE *);
char *extraer(FILE *);
byte byteToBits(char);
unsigned prepararFichero(FILE *);
char *byteToBynary(byte *, char *);
char *prepareString();
byte *encoding(int *, char *);
void printByte(byte);
