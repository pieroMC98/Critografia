#include "DH.h"
key_t returnKey() { return ftok("/dev/null", 1); }

int createMsgTail() { return msgget(returnKey(), 0757 | IPC_CREAT); }

li grupoZa(li p, li *j) {
	li *aux, k, *rt;
	for (int i = 1; i < p; i++) {
		aux = generadores(i, p, j, repetido);
		if (aux != NULL) {
			rt = (li *)realloc(rt, (k + 1) * sizeof(li));
			rt[k++] = i;
		}
		free(aux);
	}
	*j = k;
	return k;
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

	li *Xa = grupoZa();
	msg.value = envio;
	msg.X = exponenciacion(alfa, q, Xa);

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
