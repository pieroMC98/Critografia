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
	while (i < j) {
		if (!mod(p, criba[i])) {
			p /= criba[i];
			rt = realloc(rt, (k + 1) * sizeof(li));
			rt[k++] = criba[i];
		} else
			i++;
	}

	if (p != 1) {
		rt = realloc(rt, (k + 1) * sizeof(li));
		rt[k++] = p;
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
	li *c;
	do {
		aux = randomp(p);
		c = factorizacion(aux, &j);
	} while (j != 2);
	printf("un primo aleatorio de %lu es %lu\n", p, aux);
	free(c);
	return aux;
}

li *bezout(li a, li b) {
	li **rt = (li **)calloc(3, sizeof(li *));
	li *r = (li *)calloc(2, sizeof(li));
	for (int i = 0; i < 3; i++) rt[i] = (li *)calloc(4, sizeof(li));

	rt[0] = (li[4]){a, -1, 1, 0};
	rt[1][0] = b;
	rt[1][1] = a / b;
	rt[1][3] = 1;

	int i = 2;
	int tam;
	while ((rt[i][0] = rt[i - 2][0] % rt[i - 1][0]) > 0) {
		tam = i + 1;
		rt[i][1] = rt[i - 1][0] / rt[i][0];
		rt[i][2] = rt[i - 2][2] - rt[i - 1][2] * rt[i - 1][1];
		rt[i][3] = rt[i - 2][3] - rt[i - 1][3] * rt[i - 1][1];
		tam++;
		rt = (li **)realloc(rt, (tam) * sizeof(li *));
		rt[++i] = (li *)calloc(4, sizeof(li));
	}

	li *aux = rt[i - 1];
	r[0] = aux[2];
	r[1] = aux[3];
	// for (int j = 0; j < tam; ++j) free(rt[j]);
	free(aux);
	free(rt);
	return r;
}

void euclidesExtendido(li a, li b) {
	li i = mcd(a, b);
	li *j = bezout(a, b);
	printf("el mcd de %lu y %lu es %lu; identidad de bezout s = %lu y t = %lu\n", a, b, i, j[0], j[1]);
}

li *inverso(li a, li b) {
	if (mcd(a, b) > 1) return NULL;
	li *rt = bezout(a, b);
	rt[0] += b;
	rt[1] = b;
	return rt;
}

int op() {
	int opt;
	printf("Eliga:\n\
	  1 -> modulo \n\
	  2 -> mcd \n\
	  3 -> cribaEratostenes \n\
	  4 -> factorizacion\n\
	  5 -> generar aleatorio\n\
	  6 -> primo aleatorio\n\
	  7 -> inverso\n\
	  8 -> exponenciacion\n");

	scanf("%d", &opt);
	return opt;
}

li *exponenciacion(li a, li n) {
	li *rt, x;
	printf("ingrese el numero x\n");
	scanf("%lu", &x);

	return rt;
}

li *option(li a, li b, li p, li *j) {
	li *rt;
	int opt = op();

	*j = 1;
	switch (opt) {
		case 1:
			rt = malloc(sizeof(li));
			rt[0] = mod(a, b);
			break;
		case 2:
			rt = malloc(sizeof(li));
			rt[0] = mcd(a, b);
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
			break;
		case 6:
			rt = malloc(sizeof(li));
			rt[0] = randomOdd(p);
			break;
		case 7:
			rt = inverso(a, b);
			*j = 2;
			break;
		case 8:
			rt = exponenciacion(a, b);
			*j = 2;
			break;
		default:
			return NULL;
	}
	return rt;
}
