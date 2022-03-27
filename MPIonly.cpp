#include <mpi.h>
#include <math.h>
#include <unistd.h>
#include <algorithm>
#include <fstream>

#pragma GCC diagnostic ignored "-Wunused-value"

int main(int argc, char* argv[]) {

    int comm_size;
    int comm_rank;
    unsigned long n = 1000;
    unsigned long f_elem;
    unsigned long l_elem;
    unsigned long size;
    unsigned long i;
    unsigned long k;
    unsigned long first_multiple_index;
    unsigned long next_k;
    unsigned int count = 0;
    unsigned int global_count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    double start = MPI_Wtime();

    // we splitten de lijst in blocks voor elke process. ook zorgen we dat voor elke process de first en last elem en de size word opgeslagen.
    f_elem = floor(comm_rank * (n - 2) / comm_size) + 2;
    l_elem = floor((comm_rank + 1) * (n - 2) / comm_size) - 1 + 2;
    size = l_elem - f_elem + 1;

    // we initialiseren een lijst met daarin elementen tot size die true zijn
    bool *array = new bool[size];
    for(i = 0; i < size; i++){
        array[i] = true;
    }

    k = 2;

    while(k * k <= n){
        // we bepalen de index van het eerste veelvoud van k in de huidige thread
        first_multiple_index;
        if(f_elem % k == 0) {
					first_multiple_index = 0;
				} else {
					first_multiple_index = k - f_elem % k;
				}


        // van deze eerste veelvoud marken we als een non prime voor elke n element.
        for(i = first_multiple_index; i < size; i += k){
            array[i] = false;
        }
        if(comm_rank == 0) {
					array[k - 2] = true;
				}


        // we zetten de volgende waarde van k naar de kleinste nummer en we kijken of dat groter is dat de current k
        // we geven aan dat thread 0 dit volgende waade moet gaan vinden. Dit waarde is voornamelijk in thread 0 omdat we zeggen dat n / p groter is dan sqrt(n)
        if(comm_rank == 0){
            next_k = k + 1;

            while(!array[next_k - 2]) {
							next_k = next_k + 1;
						}
            k = next_k;
        }

        // we broadcasten de volgende k naar de volgende processen.
        MPI_Bcast (&k,  1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    //we counten de totale nummers van prime en summen dat naar een variabelen.
    for(i = 0; i < size; i++){
        if (array[i]) {
          count++;
        }
    }

    MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double duration = MPI_Wtime() - start;

    if(comm_rank == 0){

        std::ofstream myFile;
        myFile.open("spreadsheet/mpionly.csv", std::ios::app);
        myFile << comm_size << "; " << duration << "; " << global_count << "; " << n << std::endl;
        myFile.close();

        std::cout << "amount of numbers: " << n << std::endl;
        std::cout << "amount of threads used: " << comm_size << std::endl;
        std::cout << size+1 << " elements per thread" << std::endl;
        std::cout << "found total prime numbers: " << global_count << std::endl;
        std::cout << "total time taken: " << duration << std::endl;
    }
    // we geven de memory weer vrij
    delete(array);

    MPI_Finalize();
}
