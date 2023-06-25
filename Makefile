# Planejado e desenvolvido por
# Guiusepe Oneda Dal Pai - GRR20210572
# Fernando Gbur dos Santos - GRR20211761

FLAGS = -O3 -mavx -march=native -O3 
OBJS = matrixOperations.c mathOperations.c iolib.c mymatheval.c

all:
		gcc ${FLAGS} pontosCriticos.c  ${OBJS} -o pontosCriticos

purge:
		-rm -f pontosCriticos
