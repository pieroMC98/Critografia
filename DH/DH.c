#include "DH.h"
key_t returnKey() { return ftok("/dev/null", 1); }

int createMsgTail() { return msgget(returnKey(), 0757 | IPC_CREAT); }

li grupoZa(li alfa, li p) {
	if (generadores(alfa, p, NULL, repetido) != NULL) return true;
	return false;
}

int run(int alfa, int q) {
	srand(time(NULL) + getpid());
	Msg msg;
	int tail = createMsgTail();
	struct msqid_ds info;

	int envio = 1;
	if ((int)!info.msg_qnum)
		envio = 1;
	else if ((int)info.msg_qnum == 1)
		envio = 2;

	if (!grupoZa(alfa, q)) return 1;
	li x = randomp(q);
	msg.value = envio;
	msg.X = *exponenciacion(alfa, q, &x);

	int rt = msgsnd(tail, (void *)&msg, sizeof(msg.X), IPC_NOWAIT);
	if (!rt) {
		printf("mensaje (%d) enviado\n", (int)msg.value);
	}

	int recibo = 0;
	if ((int)info.msg_qnum == 1)
		recibo = 2;
	else if ((int)info.msg_qnum == 2)
		recibo = 1;

	msgctl(tail, IPC_STAT, &info);
	printf("%d\n", (int)info.msg_qnum);

	rt = msgrcv(tail, &msg, sizeof(msg.X), recibo, 0);
	if (!rt) printf("Esperando mensaje\n");

	printf("mensaje = %d\n", msg.X);

	msgctl(tail, IPC_RMID, (struct msqid_ds *)NULL);

	return 0;
}
