#include "mpi.h"

#define SENDER   0
#define RECEIVER 1

int my_rank, data;

void exchange_data() {
  if (my_rank == SENDER)
    MPI_Send(&data, 1, MPI_INT, RECEIVER, 0, MPI_COMM_WORLD);
  else if (my_rank == RECEIVER)
    MPI_Recv(&data, 1, MPI_INT, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  // Fetch the rank of current process (it's the same in 
  // both MPI implementations, either one can be used)
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  // Start with OpenMPI (could be configured using the 
  // S4BXI_SMPI_IMPLEM=0 environment variable instead)
  s4bxi_use_smpi_implem(0);

  // Exchange data using OpenMPI: SENDER will send "42" to RECEIVER
  if (my_rank == SENDER)
    data = 42;
  exchange_data();

  // Switch to SMPI
  s4bxi_use_smpi_implem(1);

  // Exchange data using SMPI: SENDER will send "43" to RECEIVER
  if (my_rank == SENDER)
    data = 43;
  exchange_data();

  MPI_Finalize();
  return 0;
}
