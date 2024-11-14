/// Trey Rubino

#ifndef UTILITY_H
#define UTILITY_H

#include <string>

/// Custom stateless utility class for file data and response building.
struct Utility 
{
    /// getMimeType
    /// @brief Exacts the mime type of the request file for response buildling.
    /// @param 		std::string &path	- pointer to the file being requested
    /// @return		std::string 		- the file mime type
    static std::string getMimeType(const std::string &path);

    /// fileExists
    /// @brief Checks if file exists and handles errors.
    /// @param 		std::string &path	- pointer to the file being requested
    /// @return		bool			- true or false if file exists 
    static bool fileExists(const std::string &path);
    
    /// readFile
    /// @brief Reads the contents of the request file.
    /// @param 		std::string &path	- pointer to the file being requested
    /// @return		std::string 		- contents of the file
    static std::string readFile(const std::string &path);

    /// generateResponse
    /// @brief Builds the response string to send back to the client.
    /// @param 		std::string &directory  - pointer tp the server main root dir
    /// @param 		std::string &path	- pointer to the file being requested
    /// @return		std::string		- response string to send
    static std::string generateResponse(const std::string &directory, const std::string &path);

    /// validateFilePath
    /// @brief Makes sure that the file path is within the servers directory.
    /// @param 		std::string &directory 	- pointer to the server main root dir
    /// @param		std::string &path	- pointer to the file being requested
    /// @return		bool			- false if not in scope, true othewise
    static bool validateFilePath(const std::string &directory, const std::string &path);
};

#endif
