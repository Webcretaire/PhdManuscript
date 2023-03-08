// Interception in the header file that's injected in user code
MPI_Request S4BXI_MPI_REQUEST_NULL();
#define MPI_REQUEST_NULL (S4BXI_MPI_REQUEST_NULL())

// Implementation in our simulator
MPI_Request S4BXI_MPI_REQUEST_NULL()
{
    BxiMainActor* main_actor = GET_CURRENT_MAIN_ACTOR;
    return (main_actor->use_smpi_implem ? NULL : main_actor->bull_mpi_ops->REQUEST_NULL);
    //                                    .       ,
    //                          SMPI value           OpenMPI value
}