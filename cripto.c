#include "cripto.h"

void print(li *v, int N) {
	printf("Resultado:\n");
	for (int i = 0; i < N; i++) {
		printf("%ld ", v[i]);
	}
	printf("\n");
}

li *cribaEratostenes(li N, li *j) {
	li *m = (li *)calloc(N + 1, sizeof(li));
	li *rt = (li *)calloc(1, sizeof(li));
	m[0] = m[1] = false;
	for (int i = 2; i <= N; ++i) m[i] = i;
	for (int i = 2; i * i <= N; ++i)
		if (m[i])
			for (int h = 2; i * h <= N; ++h) m[i * h] = false;

	*j = 0;
	for (int i = 0; i <= N; i++)
		if (m[i]) {
			rt = (li *)realloc(rt, (*j + 1) * sizeof(li));
			rt[(*j)++] = m[i];
		}

	free(m);
	return rt;
}

li mod(li a, li b) { return a % b; }

li mcd(li a, li b) {
	if (!b) return a;
	return mcd(b, mod(a, b));
}

li randomp(li p) { return 1 + rand() % p; }

li *factorizacion(li p, li *N) {
	li i = 0, j;
	li k = 0;
	li *criba, *rt = (li *)calloc(1, sizeof(li));

	criba = cribaEratostenes((li)sqrtl(p), &j);
	print(criba,j);
	while (p >= criba[i]) {
		if (!mod(p, criba[i])) {
			p /= criba[i];
			rt = realloc(rt, (k + 1) * sizeof(li));
			rt[k++] = criba[i];
		} else
			i++;
	}

	rt = realloc(rt, (k + 1) * sizeof(li));
	*N = k + 1;
	rt[k] = 1;
	free(criba);
	return rt;
}

li randomOdd(li p) {
	li j;
	li aux;
	do {
		aux = randomp(p);
		factorizacion(aux, &j);
	} while (j != 2);
	printf("un primo aleatorio de %lu es %lu\n",p,aux);
	return aux;
}

li *option(li a, li b, li p, li *j) {
	li *rt;
	int opt;
	printf("Eliga:\n\
	  1 -> modulo \n\
	  2 -> mcd \n\
	  3 -> cribaEratostenes \n\
	  4 -> factorizacion\n\
	  5 -> generar aleatorio\n\
	  6 -> primo aleatorio\n\
	  7 -> inverso\n");

	scanf("%d", &opt);

	switch (opt) {
		case 1:
			rt = malloc(sizeof(li));
			rt[0] = mod(a, b);
			*j = 1;
			break;
		case 2:
			rt = malloc(sizeof(li));
			rt[0] = mcd(a, b);
			*j = 1;
			break;
		case 3:
			rt = cribaEratostenes(a, j);
			break;
		case 4:
			rt = factorizacion(p, j);
			break;
		case 5:
			rt = malloc(sizeof(li));
			rt[0] = randomp(p);
		case 6:
			rt = malloc(sizeof(li));
			rt[0] = randomOdd(p);
		case 7:
			;
		default:
			return NULL;
	}
	return rt;
}
