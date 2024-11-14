/// Trey Rubino

#ifndef UTILITY_H
#define UTILITY_H

#include <stdbool.h>

void parser(int argc, char * argv[], int *seed, int *N, int *num_threads);
void print_instructions();

/* Description: check if an array is sorted in ascending order
 *
 * Parameters: int* arr: the array to check
 *             int size: the size of the array
 *
 * Return Value: true if the array is sorted, otherwise false
 */
bool check_sort(int* arr, int size);

/* Description: print an array of integers to stdout
 *
 * Parameters: int* arr: the array to check
 *             int size: the size of the array
 *
 * Return Value: none
 */
void print_array(int *arr, int size);

#endif // UTILITY_H
