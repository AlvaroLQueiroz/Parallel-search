rm -f result.data &&
make &&
time mpiexec -np 4 ./busca_paralela dados.dat 10
