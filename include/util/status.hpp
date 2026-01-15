#ifndef STATUS_HPP
#define STATUS_HPP

#include <iostream>
#include <string>
#include <cstdarg>
#include <vector>

namespace status_utils{


enum class StatusCode{
    OK,     // Use when the situation is what it's supposed to be
    ERROR,  // Use when the situation fails in an unexpected way 
    FAILED  // Use when the situation fails in a known and expected way
};


/**
 * @brief Convert a status code to its string equivalent
 * 
 * @param status The status to convert
 * @return `std::string` The string equivalent of the status
 */
std::string status_to_string(StatusCode status);


/**
 * @brief Checks if all of the statuses are OK and returns true if they are,
 *  if not, then return false
 * 
 * @param statuses `std::vector<StatusCode>` Vector of statuses to check 
 * @return `bool` True if all are OK, false if they're not
 */
bool statuses_OK(std::vector<StatusCode> statuses);


/**
 * @brief Print the status
 * 
 * @param status The status to print 
 */
void print_status(StatusCode status);


template<typename T>

struct StatusedValue{

    T value;
    StatusCode status;
    
    StatusedValue(T _value, StatusCode _status) : value(_value), status(_status){}


    /**
     * @brief Gets if the status is OK or not
     * 
     * @return `bool` True if the status is OK
     */
    bool is_OK()
    {
        // Return true if the status is OK
        return status == StatusCode::OK;

    } // end of "is_OK"

    
    /**
     * @brief Gets the status as a string
     * 
     * @return `std::string` The string representation 
     */
    std::string to_string()
    {
        // Return the string representation
        return status_utils::status_to_string(status);

    } // end of "to_string"

}; // struct StatusedValue

} // namespace status_util

#endif // STATUS_HPP