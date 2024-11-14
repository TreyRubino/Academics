/// Trey Rubino

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  

#include "utility.h"

/// parser implementation
void parser(int argc, char *argv[], Options *options)
{
	int opt;
	
	while ((opt = getopt(argc, argv, "ih:p:f:v")) != -1) {
		switch (opt) {
			case 'i':
				print_instructions();
				exit(0);
			case 'h':
				options->host = optarg;
				break;
			case 'p':
				options->port = optarg;
				break;
			case 'f':
				options->file_path = optarg;
				break;
			case 'v':
				options->verbose = 1;
				break;
			default:
				print_instructions();
				exit(EXIT_FAILURE);
		}
	}
}


/// print_instructions implemenation
void print_instructions()
{
	printf("Usage of this program:\n"
		"-i prints the usage instructions\n"
		"-h <string> 	(optional) name of the host\n"
		"-p <string> 	(optional) port number to use\n"
		"-f <string> 	(optional) path to the file to present\n"
		"-v  		(optional) flag to set verbose mode\n"); 
}
