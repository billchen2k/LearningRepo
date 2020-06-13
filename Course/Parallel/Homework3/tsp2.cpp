/**
 * @file TSP1.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 使用 MPI 实现的一个树搜索问题。在这个实现中，每个进程一旦发现新的最佳回路后，要将最佳回路的代价发送给其他所有进程。
 * @version 0.1
 * @date 2020-06-10 16:09
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <mpi.h>
#include <stdio.h>
#include <stack>
#include <iostream>

using namespace std;

int main() {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();
}