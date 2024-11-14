/// Trey Rubino

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utility.h"

/// parse command line arguments
void parser(int argc, char *argv[], int *seed, int *N, int *num_threads)
{
        int opt;
        int tflag = 0, nflag = 0, sflag = 0;

        while ((opt = getopt(argc, argv, "hs:t:n:")) != -1) {
                switch (opt) {
                        case 'h':
                                print_instructions();
                                exit(0);
                        case 's':
                                *seed = atoi(optarg);
                                sflag = 1;
                                break;
                        case 'n':
                                *N = atoi(optarg);
                                nflag = 1;
                                break;
                        case 't':
                                *num_threads = atoi(optarg);
                                tflag = 1;
                                break;
                        default:
                                print_instructions();
                                exit(EXIT_FAILURE);
                }
        }

        if (!sflag || !nflag || !tflag) {
                printf("Error: Missing required options.\n");
                print_instructions();
                exit(EXIT_FAILURE);
        }
}

/// print intrsuctions of the program
void print_instructions()
{
        printf("Usage of this program:\n"
                "-h prints the usage instructions\n"
                "-t <double> (required) number of threads to use\n"
                "-n <double> (required) size of the array to sort\n"
                "-s <double> (required) seed for the random number generator\n");
}

bool check_sort(int* arr, int size) {
    bool result = true;
    for (int i = 0; i < size-1; i++) {
        if (arr[i+1] < arr[i]) {
            result = false;
            break;
        }
    }
    return result;
}

void print_array(int *a, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
