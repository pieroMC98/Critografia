#include "cripto.h"

void print(li *v, int N) {
	printf("Resultado:\n");
	for (int i = 0; i < N; i++) {
		printf("%lld ", v[i]);
	}
	printf("\n");
}

li *primeNext(li l0, li sum, li *size) {
	li j;
	li *rt = cribaEratostenes(l0 + sum, &j);
	li *prin_gen = (li *)malloc(sizeof(li));
	*size = 0;
	for (li k = 0; k < j; k++)
		if (rt[k] >= l0) {
			prin_gen = (li *)realloc(prin_gen, (*size + 1) * sizeof(li));
			prin_gen[(*size)++] = rt[k];
		}

	free(rt);
	return prin_gen;
}

li *gordon(li l0, li sum) {
	li s, t, j, p0, *c, r;
	li *previous = cribaEratostenes(l0, &s);
	s = previous[s - 1];
	free(previous);
	li *next = primeNext(l0, sum, &t);
	t = next[t - 1];
	free(next);
	li *aux = malloc(sizeof(li));
	printf("En una longitud de %llu, el primo previo es %llu y el siguiente %llu para '%lld'\n", sum, s, t, l0);
	li i = 1;
	do {
		r = 2 * t * i + 1;
		c = factorizacion(r, &j);
		printf("\npara i = %lld, $r\\leftarrow 2*t*i+1 = %lld$\nfactores de r ", i, r);
		print(c, j);
		i++;
	} while (j != 2);

	*aux = r - 2;
	li *exp = exponenciacion(s, r, aux);
	p0 = 2 * s * (*exp) - 1;
	li p;
	printf("\npara $i = %lld$, $r\\leftarrow = %lld$ Y $p0 \\leftarrow 2s(s^{r-2} mod(r)) - 1 = %lld$\n", i, r, p0);
	i = 1;
	do {
		p = p0 + 2 * i * r * s;
		c = factorizacion(p, &j);
		printf("\npara $j = %lld$, $p \\leftarrow p0 + 2 * j * r * s = %lld$\nfactores de r ", i, p);
		print(c, j);
		i++;
	} while (j != 2);
	printf("\nsolucion $j = %lld$, $r \\leftarrow 2*t*i+1 = %lld$ Y $p0 \\leftarrow 2s(s^{r-2} mod(r)) - 1 = %lld$ y $p = %llu$\n", i, r, p0,
	       p);
	li tam;
	aux = factorizacion(p,&tam);
	print(aux,tam);
	*aux = p;
	return aux;
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
	p = (long long)pow(2, 64) / 2;
	printf("%lld\n", p);
	do {
		aux = randomp(p);
		c = factorizacion(aux, &j);
	} while (j != 2);
	printf("un primo aleatorio de %llu es %llu\n", p, aux);
	free(c);
	return aux;
}

li *bezout(li a, li b) {
	li **rt = (li **)calloc(2, sizeof(li *));
	for (int i = 0; i < 2; i++) rt[i] = (li *)calloc(4, sizeof(li));
	li *r = (li *)calloc(2, sizeof(li));
	li noZero;

	rt[0] = (li[]){a, -1, 1, 0};
	rt[1][0] = b;
	rt[1][1] = a / b;
	rt[1][3] = 1;

	int i = 2, tam;
	while (1) {
		noZero = rt[i - 2][0] % rt[i - 1][0];
		tam = i + 1;
		if (noZero)
			rt = (li **)realloc(rt, (tam) * sizeof(li *));
		else
			break;

		rt[i] = (li *)calloc(4, sizeof(li));
		rt[i][0] = noZero;

		rt[i][1] = rt[i - 1][0] / rt[i][0];
		rt[i][2] = rt[i - 2][2] - rt[i - 1][2] * rt[i - 1][1];
		rt[i][3] = rt[i - 2][3] - rt[i - 1][3] * rt[i - 1][1];
		i++;
	}

	li *aux = rt[i - 1];
	r[0] = aux[2];
	r[1] = aux[3];
	free(aux);
	free(rt);
	return r;
}

void euclidesExtendido(li a, li b) {
	li i = mcd(a, b);
	li *j = bezout(a, b);
	printf("el mcd de %llu y %llu es %llu; identidad de bezout s = %llu y t = %llu\n", a, b, i, j[0], j[1]);
}

li *inverso(li a, li b) {
	if (mcd(a, b) > 1) return NULL;
	li *rt = bezout(a, b);
	rt[0] += b;
	rt[1] = b;
	return rt;
}

int op(li a, li b, li p) {
	int opt;
	printf("Eliga:\n\
	  1 -> modulo \n\
	  2 -> mcd \n\
	  3 -> cribaEratostenes \n\
	  4 -> factorizacion\n\
	  5 -> generar aleatorio\n\
	  6 -> primo aleatorio\n\
	  7 -> inverso\n\
	  8 -> exponenciacion\n\
	  9 -> generadores del grupo z\n\
	  10 -> elemento pertenece a grupo z\n\
	  11 -> simbolo de legendre\n\
	  12 -> simbolo de jacobi\n\
	  para los argumentos a = %llu, b = %llu, c = %llu\n",
	       a, b, p);
	scanf("%d", &opt);
	return opt;
}

li *legendre(li a, li p) {
	if (1 > a || a >= p) return NULL;
	if (mcd(a, p) != 1) return NULL;

	li *exp = (li *)malloc(sizeof(li));
	*exp = (p - 1) / 2;
	li *rt = exponenciacion(a, p, exp);

	free(exp);
	if (*rt != 1)
		if ((p - 1) == *rt) *rt = -1;
	return rt;
}

li *jacobi(li a, li b) {
	li j;
	li *rt = factorizacion(b, &j);
	li *sol = (li *)malloc(sizeof(li));
	*sol = 1;
	for (int i = 0; i < j - 1; i++) *sol *= *legendre(a, rt[i]);

	free(rt);
	return sol;
}

li *exponenciacion(li a, li n, li *legendre) {
	li *rt = (li *)calloc(1, sizeof(li)), x;
	if (legendre == NULL) {
		printf("ingrese el numero x\n");
		scanf("%llu", &x);
	} else
		x = *legendre;

	li accum = 1, apow;
	apow = a;
	while (1) {
		if (x & 0x01) {
			accum = (accum * apow) % n;
			rt[0] = accum;
		}
		x >>= 1;
		if (x == 0) break;
		apow = (apow * apow) % n;
	};

	return rt;
}

li repetido(li x, li *v, li i) {
	for (li j = 0; j < i; j++) {
		if (v[j] == x) return 1;
	}
	return 0;
}

li *generadores(li p, li n, li *tam, li (*rep)(li, li *, li)) {
	li *zp = (li *)calloc(n - 1, sizeof(li)), x = n - 1;
	li accum = 1, apow;
	apow = p;
	li i = 0;

	for (x = n - 1; x > 0; x--) {
		accum = (accum * apow) % n;
		*tam = i + 1;
		zp[i++] = accum;
	}

	if (rep != NULL)
		for (int j = 1; j < i; j++)
			if (rep(zp[j], zp, j - 1)) {
				free(zp);
				return NULL;
			}

	return zp;
}

li *option(li a, li b, li p, li *j) {
	li *rt = NULL, *aux = NULL;
	int opt = op(a, b, p);

	*j = 1;
	li x;
	int k = 0;
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
			rt = exponenciacion(a, b, NULL);
			*j = 1;
			break;
		case 9:
			for (int i = 1; i < p; i++) {
				aux = generadores(i, p, j, repetido);
				if (aux != NULL) {
					rt = (li *)realloc(rt, (k + 1) * sizeof(li));
					rt[k++] = i;
				}
				free(aux);
			}
			*j = k;
			break;
		case 10:
			printf("valor a buscar\n");
			scanf("%llu", &x);
			rt = generadores(x, p, j, repetido);
			break;
		case 11:
			rt = legendre(a, p);
			break;
		case 12:
			rt = jacobi(a, p);
			break;
		default:
			return NULL;
	}
	return rt;
}
