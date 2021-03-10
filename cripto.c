#include "cripto.h"

void print(li *v, int N) {
	printf("Resultado:\n");
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

li random(li p) { return 1 + rand()%p; }

li* factorizacion(li p, li *N) {
	li i = 0, j;
	li k = 0;
	li *criba = cribaEratostenes(2, &j), *rt = (li *)calloc(1, sizeof(li));

	printf("factorizacion\n");
	while (p >= criba[i]) {
		free(criba);
		criba = cribaEratostenes(p, &j);
		if (!mod(p, criba[i])) {
			p /= criba[i];
			rt = realloc(rt, (k + 1) * sizeof(li));
			rt[k++] = criba[i];
		} else
			i++;
	}
	*N = k;
	free(criba);
	return rt;
}

li randomOdd(li p) {
	li j;
	li* c = cribaEratostenes(p,&j);
	print(c,j);
	//if(p == [j-1]);
	while( p != c[j-1]) {
		p = random(p);
		printf("\n%lu\n",p);
		c = cribaEratostenes(p,&j);
	}
	printf("resul -> %lu %lu\n",p,c[j-1]);
	//while( )
	return 1;
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
	  6 -> primo aleatorio\n");

	scanf("%d",&opt);
	if (opt < 1 || opt > 6)
		return NULL;
	
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
			rt = factorizacion(p,j);
			break;
		case 5:
			rt = malloc(sizeof(li));
			rt[0] = random(p);
		case 6:
			rt = malloc(sizeof(li));
			rt[0] = randomOdd(p);
		default:
			return NULL;
	}
	return rt;
}
