/// Trey Rubino

#include <sys/stat.h>
#include <fstream>
#include <sstream>

#include "Utility.h"

std::string Utility::getMimeType(const std::string &path) 
{
    /// if .html is not not found (npos) which means its found 
    if (path.find(".html") != std::string::npos) {
        return "text/html";
    }

    return "text/plain";
}

bool Utility::fileExists(const std::string &path) 
{
    struct stat buffer; /// stat is a system call that builds a struct of file information (size, permissions)

    return (stat(path.c_str(), &buffer) == 0); /// if there is file information, return true
}

std::string Utility::readFile(const std::string &file_path) 
{
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return ""; /// not open, return empty string
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

std::string Utility::generateResponse(const std::string &directory, const std::string &file_path) 
{
    std::string status;

    bool is_valid = validateFilePath(directory, file_path); 

    if (!is_valid) {
	status = "403 Unauthorized"; 	    
    } else if (!fileExists(file_path)) {
        status = "404 Not Found";
    } else {
	status = "200 OK";
    }

    std::string file_content = readFile(file_path);
    std::string mime_type = getMimeType(file_path);
    std::stringstream response;

    response << "HTTP/1.1 " << status << "\r\n"
             << "Content-Type: " << mime_type << "\r\n"
             << "Content-Length: " << file_content.size() << "\r\n"
             << "Connection: close\r\n\r\n"
             << file_content;

    return response.str();
}

bool Utility::validateFilePath(const std::string &directory, const std::string &path)
{
    if (path.find("..") != std::string::npos) {
	return false;
    }

    return true;
} 
