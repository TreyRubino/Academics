/// Trey Rubino

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

/// Thread function that runs the full quicksort logic, including threading
void *quicksort_thread(void *argc)
{
    thread_info_t *info = (thread_info_t *)argc;
    if (info == NULL) {
        fprintf(stderr, "Thread received NULL info.\n");
        pthread_exit(NULL);
    }

    quicksort_parallel(info->a, info->low, info->high, info->available_threads);

    free(info); 
    pthread_exit(NULL);
}

/// parallel quicksort implementation
void quicksort_parallel(int *a, int low, int high, int available_threads)
{
    if (low < high) {
        int pivot_position = median_of_three(a, low, high);
        int pivot = partition(a, low, high, pivot_position);

        pthread_t left_thread, right_thread;
        int left_thread_created = 0, right_thread_created = 0;
        int ret;

        /// Left Partition
        if ((pivot - 1 - low) > 0) {
            if (available_threads > 1) {
                int left_available_threads = available_threads - 1;
                printf("Creating thread for left partition (%d - %d), remaining threads: %d\n",
                       low, pivot - 1, left_available_threads);

                thread_info_t *left_info = malloc(sizeof(thread_info_t));
                if (left_info == NULL) {
                    perror("Failed to allocate memory for left thread info");
                    /// Exiting the thread due to a critical error
                    pthread_exit(NULL);
                }

                left_info->a = a;
                left_info->low = low;
                left_info->high = pivot - 1;
                left_info->available_threads = left_available_threads;

                ret = pthread_create(&left_thread, NULL, quicksort_thread, left_info);
                if (ret != 0) {
                    fprintf(stderr, "Failed to create left sorting thread: %s\n", strerror(ret));
                    free(left_info);
                    /// Exiting the thread due to a critical error
                    pthread_exit(NULL);
                } else {
                    left_thread_created = 1;
                }
            } else {
                printf("No threads left for left partition (%d - %d), using sequential sort\n",
                       low, pivot - 1);
                quicksort(a, low, pivot - 1);
            }
        }

        /// Right Partition
        if ((high - (pivot + 1)) > 0) {
            if (available_threads > 1) {
                int right_available_threads = available_threads - 1;
                printf("Creating thread for right partition (%d - %d), remaining threads: %d\n",
                       pivot + 1, high, right_available_threads);

                thread_info_t *right_info = malloc(sizeof(thread_info_t));
                if (right_info == NULL) {
                    perror("Failed to allocate memory for right thread info");
                    /// Exiting the thread due to a critical error
                    pthread_exit(NULL);
                }

                right_info->a = a;
                right_info->low = pivot + 1;
                right_info->high = high;
                right_info->available_threads = right_available_threads;

                ret = pthread_create(&right_thread, NULL, quicksort_thread, right_info);
                if (ret != 0) {
                    fprintf(stderr, "Failed to create right sorting thread: %s\n", strerror(ret));
                    free(right_info);
                    /// Exiting the thread due to a critical error
                    pthread_exit(NULL);
                } else {
                    right_thread_created = 1;
                }
            } else {
                printf("No threads left for right partition (%d - %d), using sequential sort\n",
                       pivot + 1, high);
                quicksort(a, pivot + 1, high);
            }
        }

        /// Wait for threads to finish
        if (left_thread_created) {
            ret = pthread_join(left_thread, NULL);
            if (ret != 0) {
                fprintf(stderr, "Failed to join left sorting thread: %s\n", strerror(ret));
                /// Exiting the thread due to a critical error
                pthread_exit(NULL);
            }
        }
        if (right_thread_created) {
            ret = pthread_join(right_thread, NULL);
            if (ret != 0) {
                fprintf(stderr, "Failed to join right sorting thread: %s\n", strerror(ret));
                /// Exiting the thread due to a critical error
                pthread_exit(NULL);
            }
        }
    }
}

// Sequential quicksort implementation
void quicksort(int *arr, int low, int high)
{
    while (low < high) {
        int pivot_position = median_of_three(arr, low, high);
        int pivot = partition(arr, low, high, pivot_position);

        if (pivot - low < high - pivot) {
            quicksort(arr, low, pivot - 1);
            low = pivot + 1;
        } else {
            quicksort(arr, pivot + 1, high);
            high = pivot - 1;
        }
    }
}

void swap(int *p1, int *p2)
{
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

int median_of_three(int *arr, int low, int high)
{
    int mid = (low + high) / 2;
    if (arr[high] < arr[low]) {
        swap(&arr[high], &arr[low]);
    }
    if (arr[mid] < arr[low]) {
        swap(&arr[mid], &arr[low]);
    }
    if (arr[high] < arr[mid]) {
        swap(&arr[high], &arr[mid]);
    }
    return mid;
}

int partition(int *arr, int low, int high, int pivot)
{
    int pivot_value = arr[pivot];
    swap(&arr[pivot], &arr[high]);

    int k = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot_value) {
            swap(&arr[j], &arr[k]);
            k++;
        }
    }
    swap(&arr[k], &arr[high]);
    return k;
}
