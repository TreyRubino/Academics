#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "parse.h"
 
/// printInstructions
/// @brief Prints the usage instructions to the console.
void printInstructions()
{
        printf("Usage of this program:\n"
                "-h prints the usage instructions\n"
                "-c <double> (required) cost of the house\n"
                "-f <double> (required) cost of fuel\n"
                "-t <double> (required) tax rate\n"
                "-y <integer> (optional) number of years - Default: 5\n");
}

/// parser
/// @brief Uses getopt() to handle options passed when running the script. Sets flags to determine which variable to set.
/// @param 	int argc 		- Count of the number of options being passed to this program.
/// @param	char *argv[] 		- Pointer to argv array which contains the values passed of each option.
/// @param 	double *initialCost 	- Pointer to the declared initialCost double in main.c. i.e. 6500.00
/// @param 	double *annualFuelCost 	- Pointer to the delcared annualFuelCost in main.c. i.e. 600.00
/// @param	double *taxRate		- Pointer to the declared taxRate variable in main.c. i.e. 0.25 
/// @param	int *years		- Option pointer to the declared years variable in main.c. Default to 5.
void parser(int argc, char *argv[], double *initialCost, double *annualFuelCost, double *taxRate, int *years)
{
	int opt;
	int cflag = 0, fflag = 0, tflag = 0;

	while ((opt = getopt(argc, argv, "hc:f:t:y:")) != -1) {
		switch (opt) {
			case 'h':
				printInstructions();
				exit(0);
			case 'c':
				*initialCost = atof(optarg);
				cflag = 1;
				break;
			case 'f':
				*annualFuelCost = atof(optarg);
				fflag = 1;
				break;
			case 't':
				*taxRate = atof(optarg);
				tflag = 1;
				break;
			case 'y':
				*years = atoi(optarg);
				break;
			default:
				printInstructions();
				exit(EXIT_FAILURE);
		}
	}
	
	if (!cflag || !fflag || !tflag) {
		printf("Error: Missing required options.\n"); 
		printInstructions();
		exit(EXIT_FAILURE);
	}
}
