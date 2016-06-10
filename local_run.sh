rm -f result.data
make
time mpiexec -np $1 ./busca_paralela $2 $3
