/// Trey Rubino

#ifndef UTILITY_H
#define UTILITY_H

#include <string>

/// Custom stateless utility class for file data and response building.
struct Utility 
{
    /// Encodes a 32-bit integer into a 4-byte big-endian format.
    /// Used for sending integer values over the network in a standardized format.
    /// @param      num         -   The integer to encode.
    /// @return A string containing the 4-byte big-endian representation of the integer.
    static std::string encodeInt32(int num);
};

#endif
