# Planejado e desenvolvido por
# Guiusepe Oneda Dal Pai - GRR20210572
# Fernando Gbur dos Santos - GRR20211761

CFLAGS = -O3 -mavx -march=native -O3 -DLIKWID_PERFMON -g -I${LIKWID_INCLUDE}
LFLAGS = -lm -L${LIKWID_LIB} -llikwid
OBJS = matrixOperations.c mathOperations.c iolib.c mymatheval.c

all:
		gcc ${CFLAGS} pontosCriticos.c  ${OBJS} -o pontosCriticos $(LFLAGS)

purge:
		-rm -f pontosCriticos