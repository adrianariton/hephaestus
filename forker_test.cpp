#include <iostream>
#include "omp.h" // ln -s /opt/homebrew/Cellar/libomp/16.0.0/include/omp.h omp.h
#include <unistd.h>
// g++-11 -fopenmp forker_test.cpp -o forker
#define THREAD_NUM 4
int main()
{
    omp_set_num_threads(THREAD_NUM); // set number of threads in "parallel" blocks
    #pragma omp parallel
    {
        usleep(5000 * omp_get_thread_num()); // do this to avoid race condition while printing
        std::cout << "Number of available threads: " << omp_get_num_threads() << std::endl;
        // each thread can also get its own number
        std::cout << "Current thread number: " << omp_get_thread_num() << std::endl;
        std::cout << "Hello, World!" << std::endl;
    }
    return 0;
}