#include <cmath>
#include <omp.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "merge-sort.h"

#define P float

const int nTrials = 10;
const int skipTrials = 3; // Skip first iteration as warm-up

double Stats(double & x, double & dx) {
    x  /= (double)(nTrials - skipTrials);
    dx  = sqrt(dx/double(nTrials - skipTrials) - x*x);
}

int main(int argc, char *argv[]) {

    int numLines = 0;
    std::ifstream in(argv[1]);
    std::string unused;

    while (getline(in, unused))
    {
        ++numLines;
    }

    int data[numLines];

    std::ifstream input(argv[1]);
    for (int i = 0; i < numLines; i++)
    {
        input >> data[i];
    }

    //if(argc < 2) {
    //    printf("Usage: %s {file}\n", argv[0]);
    //    exit(1);
    //}

    printf("\033[1m%5s %15s\033[0m\n", "Step", "Time, ms"); 
    fflush(stdout);

    double t, dt;

    for (int iTrial = 1; iTrial <= nTrials; iTrial++) {
        const double t0 = omp_get_wtime();
        // Run Merge Sort
        merge_sort(data, 0, numLines - 1);
        const double t1 = omp_get_wtime();

        const double ts   = t1-t0; // time in seconds
        const double tms  = ts*1.0e3; // time in milliseconds

        if (iTrial > skipTrials) { // Collect statistics
            t  += tms; 
            dt += tms*tms;
        }

        // Output performance
        printf("%5d %15.3f %s\n", 
                iTrial, tms, (iTrial<=skipTrials?"*":""));
        fflush(stdout);
    }

    std::string argv1(argv[1]);
    std::string result = "result_" + argv1;
    std::ofstream myfile (result.c_str());

    if (myfile.is_open())
    {

        for (int i = 0; i < numLines; i++)
        {
            myfile << data[i] << "\n";
        }

        myfile.close();
    } 
    else 
    {
        std::cout << "No se pudo abrir el archivo";
    }


    Stats(t, dt);  
    printf("-----------------------------------------------------\n");
    printf("\033[1m%s\033[0m\n%8s   \033[42m%8.1f+-%.1f\033[0m   \033",
            "Average performance:", "", t, dt);
    printf("-----------------------------------------------------\n");
    printf("* - wwarm-up, not included in average\n\n");

}
