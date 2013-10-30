//
// máximo divisor comum entre 3 números
// versao em MPI
//
// E' preciso 4 processos do programa!
// $ mpirun -np 4 gcd

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "gcd.h"

void Master(int, int, int);
void Slave(int rank);

//
//
int main(int argc, char** argv)
{
    int myRank;
    int x, y, z;

    if (argc != 4)
    {
	
	// MPI_Send(buf);
	puts("argc != 4");
	// MPI_Send(buf);
	return 1;
    }
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if (myRank == 0)
    {
    	x = atoi(argv[1]);
    	y = atoi(argv[2]);
    	z = atoi(argv[3]);
        Master(x, y, z);
    }
    else
    {
        Slave(myRank);
    }
    //printf("myRank = %d\n", myRank);
    MPI_Finalize();
    return 0;
}


//
//  processo principal
//
void Master(int x, int y, int z)
{
    int buf[3];

    // envia x e y
    buf[0] = x;
    buf[1] = y;
    MPI_Send(buf, 2, MPI_INT, 1, 1, MPI_COMM_WORLD);

    // envia y e z
    buf[0] = y;
    buf[1] = z;
    MPI_Send(buf, 2, MPI_INT, 2, 1, MPI_COMM_WORLD);

    MPI_Recv(buf, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
    x = buf[0];

    MPI_Recv(buf, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
    y = buf[0];

    if (x > 1 && y > 1)
    {
        buf[0] = x;
        buf[1] = y;
        MPI_Send(buf, 2, MPI_INT, 3, 1, MPI_COMM_WORLD);
        MPI_Recv(buf, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
        z = buf[0];
    }
    else
    {
        buf[0] = -1;
        buf[1] = -1;
        MPI_Send(buf, 2, MPI_INT, 3, 1, MPI_COMM_WORLD);
        MPI_Recv(buf, 1, MPI_INT, 3, 2, MPI_COMM_WORLD, &status);
        z = 1;
    }
    printf("resultado = %d\n", z);
}


//
// processo que faz a computacao
//
void Slave(int rank)
{
    int buf[2];

    MPI_Recv(buf, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    while (buf[0] != buf[1])
    {
        if (buf[0] < buf[1])
            buf[1] = buf[1] - buf[0];
        else
            buf[0] = buf[0] - buf[1];
    }
    MPI_Send(buf, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
}
