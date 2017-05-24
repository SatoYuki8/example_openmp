all:	sim

sim:	comp
	./no_omp
	./omp

comp:	matmul.c omp_matmul.c
	gcc -o no_omp matmul.c
	gcc -o omp -fopenmp omp_matmul.c

diff:	comp
	./no_omp > no_omp.log
	./omp > omp.log
	diff no_omp.log omp.log

distclean:	clean
	rm -rf *.log omp no_omp

clean:
	rm -rf *~