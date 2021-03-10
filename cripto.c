#include "cripto.h"

void print(li *v, int N) {
	printf("\nCriba de eratostenes es\n");
	for (int i = 0; i < N; i++) {
		printf("%lu ", v[i]);
	}
	printf("\n");
}

li *cribaEratostenes(int N, li *j) {
	li *m = (li *)calloc(N + 1, sizeof(li));
	li *rt = (li *)calloc(1, sizeof(li));
	m[0] = m[1] = false;
	for (int i = 2; i <= N; ++i) m[i] = i;
	for (int i = 2; i * i <= N; ++i)
		if (m[i])
			for (int h = 2; i * h <= N; ++h) m[i * h] = false;

	*j = 0;
	for (int i = 0; i < N; i++)
		if (m[i]) {
			printf("%lu ", m[i]);
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

li* factorizacion(li p, li *N) {
	li i = 0, j;
	li k = 0;
	li *criba = cribaEratostenes(p / 2, &j), *rt = (li *)calloc(1, sizeof(li));

	while (p != criba[i]) {
		if (!mod(p, criba[i])) {
			p /= criba[i];
			rt = realloc(rt, (k + 1) * sizeof(li));
			rt[k++] = criba[i];
		} else
			i++;
	}
	*N = k;
	return rt;
}

li *option(int opt, li a, li b, li p, li *j) {
	li *rt;
	switch (opt) {
		case 1:
			rt = malloc(8);
			rt[0] = mod(a, b);
			*j = 1;
			break;
		case 2:
			rt = malloc(8);
			rt[0] = mcd(a, b);
			*j = 1;
			break;
		case 3:
			rt = cribaEratostenes(a, j);
			break;
		case 4:
			rt = factorizacion(p,j);
			break;
		default:
			return NULL;
	}
	return rt;
}
