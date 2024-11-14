/// @author            	Trey Rubino
/// @major             	Computer Science and Mathematics
/// @creationdate      	2024-09-23
/// @duedate           	2024-09-27
/// @course            	CSC 328 010
/// @professor         	Dr. Schwesinger
/// @project           	#2
/// @filename          	main.c
/// @brief             	Takes command line arguments to create threads, and sorts
///			a randomized array of integers concurrently.                        

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> 
#include <unistd.h>

#include "sort.h"
#include "utility.h"

int main(int argc, char **argv)
{
	/// Parse command-line arguments
	int seed, N, num_threads;

	parser(argc, argv, &seed, &N, &num_threads);

	srand(seed);  /// Seed the random number generator
	int *a = calloc(N, sizeof(int));  /// Allocate memory for the array

	/// Fill the array with random numbers
	for (int i = 0; i < N; i++) {
		a[i] = rand() % 10000;
   	}
	
	/// Subtract one from the num_threads to count for the main thread
	/// being created	
	int available_threads = num_threads - 1;

   	pthread_t main_thread;
    	thread_info_t *main_info = malloc(sizeof(thread_info_t));
    	if (main_info == NULL) {
        	perror("Failed to allocate memory for thread arguments");
        	free(a);
        	exit(EXIT_FAILURE);
    	}

	main_info->a = a;
	main_info->low = 0;
	main_info->high = N - 1;
	main_info->available_threads = num_threads;
	
    	int ret = pthread_create(&main_thread, NULL, quicksort_thread, main_info);
    	if (ret != 0) {
        	fprintf(stderr, "Failed to create sorting thread: %s\n", strerror(ret));
        	free(a);
        	free(main_info);
        	exit(EXIT_FAILURE);
    	}

	printf("Hello from the main thread!\n");

    	ret = pthread_join(main_thread, NULL);
    	if (ret != 0) {
        	fprintf(stderr, "Failed to join main thread: %s\n", strerror(ret));
        	free(a);
        	exit(EXIT_FAILURE);
    	}
 
	/// Check if the array is sorted
	if (check_sort(a, N)) {
		printf("Sorted: true\n");
	} else {
		printf("Sorted: false\n");
	}

	free(a);            // Free allocated memory
	return 0;
}
