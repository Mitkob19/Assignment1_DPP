/*
 * simulate.c
 *
 * Implement your (parallel) simulation here!
 */

#include <stdio.h>
#include <stdlib.h>

#include "simulate.h"


/* Add any global variables you may need. */
double c = 0.15;

/* Ai,t+1 = 2 × Ai,t− Ai,t−1 + c × (Ai−1,t− (2 × Ai,t− Ai+1,t)) */

/* Add any functions you may need (like a worker) here. */
double equation(const double c, double Ai_t, double Ai_t_minus_1, double Ai_minus_1_t, double Ai_plus_1_t) {
    return 2 * Ai_t - Ai_t_minus_1 + c * (Ai_minus_1_t - (2 * Ai_t - Ai_plus_1_t));
}

/*
 * Executes the entire simulation.
 *
 * Implement your code here.
 *
 * i_max: how many data points are on a single wave
 * t_max: how many iterations the simulation should run
 * num_threads: how many threads to use (excluding the main threads)
 * old_array: array of size i_max filled with data for t-1
 * current_array: array of size i_max filled with data for t
 * next_array: array of size i_max. You should fill this with t+1
 */
// double *simulate(const int i_max, const int t_max, const int num_threads,
//         double *old_array, double *current_array, double *next_array)
// {
//     // for (int t = 0; t < t_max; t++) {
//     //     for (int i = 0; i < i_max; i++) {
//     //         double Ai_t = current_array[i];
//     //         double Ai_t_minus_1 = old_array[i];
//     //         double Ai_minus_1_t = current_array[i - 1];
//     //         double Ai_plus_1_t = current_array[i + 1];
//     //         double A_i_t_plus_1 = equation (c, Ai_t, Ai_t_minus_1, Ai_minus_1_t, Ai_plus_1_t);
//     //         next_array[i] = A_i_t_plus_1;
//     //     }
//     //     double *temp = old_array;
//     //     old_array = current_array;
//     //     current_array = next_array;
//     //     next_array = temp;
//     // }

//     /*
//      * After each timestep, you should swap the buffers around. Watch out none
//      * of the threads actually use the buffers at that time.
//      */


//     /* You should return a pointer to the array with the final results. */
//     return current_array;
// }

double *simulate(const int i_max, const int t_max, const int num_threads,
        double *old_array, double *current_array, double *next_array)
{
    /* Implement your sequential simulation here. */
    for (int t = 0; t < t_max; t++) {
        for (int i = 0; i < i_max; i++) {
            double Ai_t = current_array[i];
            double Ai_t_minus_1 = old_array[i];
            double Ai_minus_1_t = current_array[i - 1];
            double Ai_plus_1_t = current_array[i + 1];
            double A_i_t_plus_1 = equation (c, Ai_t, Ai_t_minus_1, Ai_minus_1_t, Ai_plus_1_t);
            next_array[i] = A_i_t_plus_1;
        }
        double *temp = old_array;
        old_array = current_array;
        current_array = next_array;
        next_array = temp;
    }
    return current_array;
}

