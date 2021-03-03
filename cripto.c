# include "header.h"

void print(li *v, int N) {
  printf("Criba de eratostenes es\n");
  for(int i = 0; i < N; i++) {
		printf("%lu ",v[i]);
	}
}

li *criba(int *N){
	printf(" n = %d ",*N);
	li i, h;
	li *m = calloc(*N, sizeof(li));
	li *rt = calloc(*N, sizeof(li));
	m[0] = m[1] = 0;
	for( i = 2; i <= *N; ++i)
	     m[i] = i;
		 for(li j = 2; j*j <= *N; ++j) {
			if(m[j]) {
				for(h = 2; j*h <= *N; ++h)
					m[j*h] = 0;
			}
		 }

	li j = 0;
	for(int i = 0; i < *N; i++)
		if( m[i] ) {
		  rt = (li*)realloc(rt, (j+1)*sizeof(li));
		  rt[j++] = m[i];
		}
	printf(" n = %lu ",j);
	
	*N = j;
	free (m);
	return rt;
}

li mod(li a, li b){
 return a % b;
}

li mcd(li a, li b) {
 return 0;
}

li cribaEratostenes(li p) {

 return 0;
}

li factorizacion(li p) {

 return 0;
}

int  option(int opt, li a, li b, li p) {
  switch(opt){
	case 1:
	  mod(a,b);
	break;
	case 2:
	  mcd(a,b);
	break;
	case 3:
	  cribaEratostenes(p);
	break;
	case 4:
	  factorizacion(p);
	  break;
	default:
	  return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if( argc <= 2) {
	  printf("parmatros para '%s' opt a b p\n", argv[0]);
	  return 1;
	}

	int opt = atoi(argv[1]);
	if(opt < 1 || opt > 4){
	  printf("opt 1 -> modulo \n\
			2 -> mcd \n\
			3 -> cribaEratostenes \n\
			4 -> factorizacion\n");
	  return 1;
	}
	  //printf("Criba de eratostenes es\n");
	int *N;
	int N1 = 6;
	N = &N1;
	print(criba(N),N1);
	int a = atol(argv[2]);
	int b = atol(argv[3]);
	int p = atol(argv[4]);

	if(!option(opt,a,b,p))
	  return 1;
return 0;
}
