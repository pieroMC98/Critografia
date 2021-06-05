#include "DH.h"

key_t returnKey() {
	key_t key = ftok("/dev/null", 1);
	if (key == -1) {
		printf("Error creacion llave papa msg\n");
		return false;
	}
	return key;
}

int createMsgTail() { return msgget(returnKey(), 0757 | IPC_CREAT); }

li grupoZa(li alfa, li p) {
	li j = 1;
	if (generadores(alfa, p, &j, repetido) != NULL) return true;
	return false;
}

int run(int alfa, int q) {
	srand(time(NULL) + getpid());
	Msg msg;
	int tail = createMsgTail();
	if (tail < 0) return EXIT_FAILURE;

	if (false == grupoZa(alfa, q)) {
		printf("alfa (%d) no es generador de q = %d\n", alfa, q);
		return EXIT_FAILURE;
	}

	struct msqid_ds info;
	msgctl(tail, IPC_STAT, &info);

	int envio = 1;
	if ((int)!info.msg_qnum)
		envio = 1;
	else if ((int)info.msg_qnum == 1)
		envio = 2;

	printf("envio es %d\n", envio);
	li x = randomp(q);

	msg.value = envio;
	msg.emisor = getpid();
	msg.X = *exponenciacion(alfa, q, &x, false);

	int rt = msgsnd(tail, (void *)&msg, sizeof(msg.X) + sizeof(msg.emisor), IPC_NOWAIT);
	if (!rt) printf("Emisor PID %d con prioridad '%ld' y X = %d\n", msg.emisor, msg.value, msg.X);

	int recibo = 0;

	msgctl(tail, IPC_STAT, &info);
	if ((int)msg.value == 1)
		recibo = 2;
	else if ((int)msg.value == 2)
		recibo = 1;

	printf("Espero mensaje tipo %d\n", recibo);
	rt = msgrcv(tail, &msg, sizeof(msg.X) + sizeof(msg.emisor), recibo, 0);
	if (rt) printf("Receptor PID %d con prioridad '%ld' y X = %d\n", msg.emisor, msg.value, msg.X);

	msgctl(tail, IPC_RMID, (struct msqid_ds *)NULL);

	return 0;
}
