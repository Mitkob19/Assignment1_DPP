/*
 * simulate.c
 *
 * Implement your (parallel) simulation here!
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "simulate.h"

double c = 0.15;

double equation(const double c, double Ai_t, double Ai_t_minus_1, double Ai_minus_1_t, double Ai_plus_1_t) {
    return 2 * Ai_t - Ai_t_minus_1 + c * (Ai_minus_1_t - (2 * Ai_t - Ai_plus_1_t));
};

/*
 * Executes the entire simulation.
 *
 *
 * i_max: how many data points are on a single wave
 * t_max: how many iterations the simulation should run
 * num_threads: how many threads to use
 * old_array: array of size i_max filled with data for t-1
 * current_array: array of size i_max filled with data for t
 * next_array: array of size i_max. You should fill this with t+1
 */
double *simulate(const int i_max, const int t_max, const int num_threads,
        double *old_array, double *current_array, double *next_array)
{
    /*
     * Your implementation should go here.
     */
    num = 5;
    #pragma omp parallel for num_threads(num)
    {
        for (i = 0; i <= 10; i++){
            #pragma omp critical{
                Ai_t = current_array[i];
                Ai_t_minus_1 = old_array[i];
                if i == 0 {
                    Ai_minus_1_t = current_array[-1];
                }
                else {
                    Ai_minus_1_t = current_array[i - 1];
                }
                Ai_plus_1_t = current_array[i + 1];
                equation(c, Ai_t, Ai_t_minus_1, Ai_minus_1_t, Ai_plus_1_t);
                double *temp = old_array;
                old_array = current_array;
                current_array = next_array;
                next_array = temp;
            }
        }
    }

    return current_array;
}
