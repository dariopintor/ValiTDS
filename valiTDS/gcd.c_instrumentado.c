#include <stdio.h>
#include <stdlib.h>
#include "valimpi.h"
#include "gcd.h"
void Master(int, int, int);
void Slave(int rank);
int
main(int argc, char * *argv)
{
    int myRank;
    int x, y, z;
    VALIMPI_TRACE_DECL;
    VALIMPI_REQ_LIST_DECL;
    ValiMPI_Req_list_init(&valimpiListReq);
    ValiMPI_Init_trace(&valimpiTrace, "main");
    ValiMPI_Check_trace(&valimpiTrace, 1);
    ValiMPI_Check_trace(&valimpiTrace, 2);
    if (argc != 4)
    {
        puts("argc != 4");
        ValiMPI_Check_trace(&valimpiTrace, 4);
        ValiMPI_Check_trace(&valimpiTrace, 15);
        return 1;
        ValiMPI_End_trace();
    }
    ValiMPI_Check_trace(&valimpiTrace, 3);
    MPI_Init(&argc, &argv);
    ValiMPI_Check_trace(&valimpiTrace, 5);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    ValiMPI_Check_trace(&valimpiTrace, 6);
    if (myRank == 0)
    {
        ValiMPI_Check_trace(&valimpiTrace, 7);
        x = atoi(argv[1]);
        ValiMPI_Check_trace(&valimpiTrace, 9);
        y = atoi(argv[2]);
        ValiMPI_Check_trace(&valimpiTrace, 10);
        z = atoi(argv[3]);
        ValiMPI_Check_trace(&valimpiTrace, 11);
        Master(x, y, z);
        ValiMPI_Check_trace(&valimpiTrace, 8);
    }
    else
    {
        ValiMPI_Check_trace(&valimpiTrace, 12);
        Slave(myRank);
        ValiMPI_Check_trace(&valimpiTrace, 13);
    }
    MPI_Finalize();
    ValiMPI_Check_trace(&valimpiTrace, 14);
    ValiMPI_Check_trace(&valimpiTrace, 15);
    return 0;
    ValiMPI_End_trace();
    ValiMPI_Check_trace(&valimpiTrace, 15);
    ValiMPI_End_trace();
}

void
Master(int x, int y, int z)
{
    int buf[3];
    VALIMPI_TRACE_DECL;
    VALIMPI_REQ_LIST_DECL;
    ValiMPI_Req_list_init(&valimpiListReq);
    ValiMPI_Init_trace(&valimpiTrace, "Master");
    ValiMPI_Check_trace(&valimpiTrace, 1);
    ValiMPI_Check_trace(&valimpiTrace, 2);
    buf[0] = x;
    ValiMPI_Check_trace(&valimpiTrace, 3);
    buf[1] = y;
    ValiMPI_Check_trace(&valimpiTrace, 4);
    ValiMPI_Send_trace(&valimpiTrace, buf, 2, MPI_INT, 1, 1, MPI_COMM_WORLD);
    ValiMPI_Check_trace(&valimpiTrace, 5);
    buf[0] = y;
    ValiMPI_Check_trace(&valimpiTrace, 6);
    buf[1] = z;
    ValiMPI_Check_trace(&valimpiTrace, 7);
    ValiMPI_Send_trace(&valimpiTrace, buf, 2, MPI_INT, 2, 1, MPI_COMM_WORLD);
    ValiMPI_Check_trace(&valimpiTrace, 8);
    ValiMPI_Recv_trace(&valimpiTrace, buf, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
    ValiMPI_Check_trace(&valimpiTrace, 9);
    x = buf[0];
    ValiMPI_Check_trace(&valimpiTrace, 10);
    ValiMPI_Recv_trace(&valimpiTrace, buf, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
    ValiMPI_Check_trace(&valimpiTrace, 11);
    y = buf[0];
    ValiMPI_Check_trace(&valimpiTrace, 12);
    if (x > 1 && y > 1)
    {
        ValiMPI_Check_trace(&valimpiTrace, 14);
        buf[0] = x;
        ValiMPI_Check_trace(&valimpiTrace, 16);
        buf[1] = y;
        ValiMPI_Check_trace(&valimpiTrace, 17);
        ValiMPI_Send_trace(&valimpiTrace, buf, 2, MPI_INT, 3, 1, MPI_COMM_WORLD);
        ValiMPI_Check_trace(&valimpiTrace, 18);
        ValiMPI_Recv_trace(&valimpiTrace, buf, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
        ValiMPI_Check_trace(&valimpiTrace, 19);
        z = buf[0];
        ValiMPI_Check_trace(&valimpiTrace, 15);
    }
    else
    {
        ValiMPI_Check_trace(&valimpiTrace, 20);
        buf[0] = -1;
        ValiMPI_Check_trace(&valimpiTrace, 22);
        buf[1] = -1;
        ValiMPI_Check_trace(&valimpiTrace, 23);
        ValiMPI_Send_trace(&valimpiTrace, buf, 2, MPI_INT, 3, 1, MPI_COMM_WORLD);
        ValiMPI_Check_trace(&valimpiTrace, 24);
        ValiMPI_Recv_trace(&valimpiTrace, buf, 1, MPI_INT, 3, 2, MPI_COMM_WORLD, &status);
        ValiMPI_Check_trace(&valimpiTrace, 25);
        z = 1;
        ValiMPI_Check_trace(&valimpiTrace, 21);
    }
    ValiMPI_Check_trace(&valimpiTrace, 13);
    printf("resultado = %d\n", z);
    ValiMPI_Check_trace(&valimpiTrace, 26);
    ValiMPI_End_trace();
}

void
Slave(int rank)
{
    int buf[2];
    VALIMPI_TRACE_DECL;
    VALIMPI_REQ_LIST_DECL;
    ValiMPI_Req_list_init(&valimpiListReq);
    ValiMPI_Init_trace(&valimpiTrace, "Slave");
    ValiMPI_Check_trace(&valimpiTrace, 1);
    ValiMPI_Check_trace(&valimpiTrace, 2);
    ValiMPI_Recv_trace(&valimpiTrace, buf, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    ValiMPI_Check_trace(&valimpiTrace, 3);
    while (ValiMPI_Check_trace(&valimpiTrace, 5), buf[0] != buf[1])
    {
        ValiMPI_Check_trace(&valimpiTrace, 6);
        if (buf[0] < buf[1])
        {
            ValiMPI_Check_trace(&valimpiTrace, 8);
            buf[1] = buf[1] - buf[0];
            ValiMPI_Check_trace(&valimpiTrace, 9);
        }
        else
        {
            ValiMPI_Check_trace(&valimpiTrace, 10);
            buf[0] = buf[0] - buf[1];
            ValiMPI_Check_trace(&valimpiTrace, 11);
        }
        ValiMPI_Check_trace(&valimpiTrace, 7);
    }
    ValiMPI_Check_trace(&valimpiTrace, 4);
    ValiMPI_Send_trace(&valimpiTrace, buf, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    ValiMPI_Check_trace(&valimpiTrace, 12);
    ValiMPI_End_trace();
}
