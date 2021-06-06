#include <sys/msg.h>
#include <sys/types.h>

#include "./entrega_pendiente/cripto/cripto.h"

typedef struct msg_buf {
	long value;
	char id;
	pid_t emisor;
	int X;
} Msg;

key_t returnKey();
int createMsgTail();
int run(int, int);
