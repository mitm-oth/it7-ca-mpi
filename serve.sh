#!/bin/bash
set -e

# build
echo "[ BUILD ] Building mpi_hello_world.c"
mpicc mpi_hello_world.c -o mpi_hello_world.out

# run
echo "[  RUN  ] Running mpi_hello_world.out"
/usr/bin/mpirun -np 4 mpi_hello_world.out

echo "[       ] Done"
