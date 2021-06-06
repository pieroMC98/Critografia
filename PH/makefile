#makfile
#macros definition

G++	   = gcc
source = *.c ./entrega_pendiente/cripto/cripto.c

debug  = -g -Wall
O 	   = -lm -o
build  = main
RUN    = ./

${build}: ${source}
	${G++} ${debug} ${source} ${O} ${build}

run: main
	@clear
	@${RUN}main
