#include "header.h"

int  option(int opt, li a, li b, li p) {
  switch(opt){
	case 1:
	  modulo(a,b);
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
	int a = atol(argv[2]);
	int b = atol(argv[3]);
	int p = atol(argv[4]);

	if(!option(opt,a,b,p))
	  return 1;
return 0;
}
