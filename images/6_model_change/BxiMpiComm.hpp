class BxiMpiComm {
  public:
    MPI_Comm bull;
    MPI_Comm smpi;

    static MPI_Comm implem_comm(MPI_Comm original);
    static MPI_Comm bull_comm(MPI_Comm original);
    static MPI_Comm smpi_comm(MPI_Comm original);
};