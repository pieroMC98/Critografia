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
	if ((int)!info.msg_qnum) {
		envio = 1;
		msg.id = 'A';
	} else if ((int)info.msg_qnum == 1) {
		envio = 2;
		msg.id = 'B';
	}

	printf("envio es %d\n", envio);
	li x = randomp(q);
	printf("X%c aleatorio = %lld\n", msg.id, x);
	msg.value = envio;
	msg.emisor = getpid();
	msg.X = *exponenciacion(alfa, q, &x, false);
	char aux_X = msg.id;

	int rt = msgsnd(tail, (void *)&msg, sizeof(msg.X) + sizeof(msg.emisor) + sizeof(msg.id), IPC_NOWAIT);
	if (!rt) printf("Emisor PID %d con prioridad '%ld' y Y%c = %d\n", msg.emisor, msg.value, msg.id, msg.X);

	int recibo = 0;

	msgctl(tail, IPC_STAT, &info);
	if ((int)msg.value == 1)
		recibo = 2;
	else if ((int)msg.value == 2)
		recibo = 1;

	printf("\nEspero mensaje tipo %d...\n", recibo);
	rt = msgrcv(tail, &msg, sizeof(msg.X) + sizeof(msg.emisor) + sizeof(msg.id), recibo, 0);
	if (rt) printf("Receptor PID %d con prioridad '%ld' y X = %d\n", msg.emisor, msg.value, msg.X);
	li k = *exponenciacion(msg.X, q, &x, false);
	printf("K = Y%c^X%c mod q = %d ^ %lld mod %d = %lld\n", msg.id, aux_X, msg.X, x, q, k);

	msgctl(tail, IPC_RMID, (struct msqid_ds *)NULL);

	return 0;
}
