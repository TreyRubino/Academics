/// Trey Rubino

#ifndef UTILITY_H
#define UTILITY_H

/// Options
/// @brief Typedef struct to contain the arguments passed to this script. This makes it easy to resure these arugments in our areas of the program.
/// @param 	char *host 		- string of the host name to send the request to. i.e. www.kutztown.edu
/// @param	char *port		- string of the port number to use. i.e. "80"
/// @param	char *file_path		- string of the file being requested from the server. i.e. "/" 
/// @param	int verbose		- integer flag to run this script in verbose mode. i.e. -v
typedef struct {
	char *host;
	char *port;
	char *file_path;
	int verbose;
} Options;

/// parser
/// @brief Uses getopt to handle the parsing of the command line arguments to this script.
/// @param	int argc		- count of command line arguments 
/// @param	char *argv[]		- pointer to the first argment
/// @param 	Options *options 	- pointer to Options struct used to hold options
void parser(int argc, char *argv[], Options *options);

/// prints program instructions
void print_instructions();

#endif
