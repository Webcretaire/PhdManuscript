#define MPI_Init(...)   S4BXI_MPI_Init(__FILE__, __LINE__, ##__VA_ARGS__)
#define MPI_Send(...)   S4BXI_MPI_Send(__FILE__, __LINE__, ##__VA_ARGS__)
#define MPI_Recv(...)   S4BXI_MPI_Recv(__FILE__, __LINE__, ##__VA_ARGS__)
// ...
