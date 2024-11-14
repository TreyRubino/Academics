/// Trey Rubino

#ifndef SORT_H
#define SORT_H

/// @brief define tpyedef struct to store thead information need for sorting
/// @param      a                       - pointer to the array being sorted
/// @param      low                     - the starting inde of the portion of the array
/// @param      high                    - The ending index of the portion of the array
/// @param      available_threads       - the number of threads to use
typedef struct {
    int *a;
    int low;
    int high;
    int available_threads;
} thread_info_t;

/// @breif Thread function that runs the parallel quicksort algorithm.
/// @param 	arg 	- pointer to thread information (contains struct of array, int  low, int  high, and int available_threads
/// @return 	void* 	- returns NULL upon thread completion. 
void *quicksort_thread(void *arg);

/// @brief Perform parallel quicksort on the given portion of the array.
/// @param      a                       - pointer to the array being sorted
/// @param      low                     - the starting index of the portion of the array
/// @param      high                    - the ending index of the portion of the array
/// @param      available_threads       - the number of available threads for parallel execution
void quicksort_parallel(int *a, int low, int high, int available_threads);

/* Description: A sequential implementation of quicksort
 *
 * Parameters: int *arr: array of integers to sort
 *             int low: the lower bound index of the sub-array to sort
 *             int high: the upper bound index of the sub-array to sort
 *
 * Return Value: none (the array is sorted in place)
 */
void quicksort(int  *arr, int low, int high);

/* Description: swap the values of two integer parameters
 *
 * Parameters: int arr: first integer (mutated to second value on return)
 *             int b: second integer (mutated to first value on return)
 *
 * Return Value: none
 */
void swap(int * p1, int * p2);

/* Description: find the index in arr sub-array corresponding to the median value
 * of the lowest, middle, and highest indices in a sub-array; this is an
 * optimization in the context of quicksort to find a good pivot.
 *
 * Parameters: int *arr: the array
 *             int low: the lowest index of the sub-array
 *             int high: the highest index of the sub-array
 *
 * Return Value: the index into the sub-array corresponding to the median value
 */
int median_of_three(int *arr, int low, int high);

/* Description: insert the pivot value into the correct sorted index in a
 * sub-array
 *
 * Postcondition: all elements in the array that are less than the pivot value
 * are in the left sub-array bounded by the pivot and all values greater than
 * pivot value are in the right sub-array bounded by the pivot value.
 *
 * Parameters: int *arr: the array
 *             int low: the lowest index of the sub-array
 *             int high: the highest index of the sub-array
 *             int pivot: the 
 *
 * Return Value: the index of the final pivot position in the array
 */
int partition(int  *arr, int low, int high, int pivot);

#endif // SORT_H
