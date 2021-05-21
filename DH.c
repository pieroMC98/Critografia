#include "cripto.h"
#include "DH.h"

typedef struct msgbuf {
	long value;
	int X;
}Msg;
key_t returnKey(){
	return ftok("/dev/null", 1);
}

int createMsgTail() {
	return msgget(returnKey(), 0755 | IPC_CREAT);
}

int run(int alfa, int q) {
	srand(time(NULL) + getpid());
	Msg msg;
	int tail = createMsgTail();
	msg.value= 1;
	msg.X = 44;
	int rt = msgsnd(tail,(void *)&msg,sizeof(msg.X),IPC_NOWAIT);
	if (!rt) {
		printf("mensaje enviado\n");
	}
	msgrcv(tail,)

	msgctl(tail,IPC_RMID, (struct msqid_ds *)NULL);

	return 0;
}
