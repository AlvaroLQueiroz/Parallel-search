rm -f result.data
time mpirun -np $1 --hostfile hosts ./busca_paralela $2 $3
