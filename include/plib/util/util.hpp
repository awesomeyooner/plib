#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <iostream>
#include <exception>
#include <sstream>
#include <iomanip>

#include "status.hpp"
#include <limits>

namespace util{


/**
 * @brief Send text to the terminal using `std::cout`
 * 
 * @param text `std::string` The text to send
 * @param should_end_line `bool` Whether or not to end the line
 */
void print(std::string text, bool should_end_line = true);


/**
 * @brief Send a number to the terminal using `std::cout`
 * 
 * @param text `double` The text to send
 * @param should_end_line `bool` Whether or not to end the line
 */
void print(double text, bool should_end_line = true);


/**
 * @brief Send text to the terminal using `std::cout`
 * 
 * @param value `float` The text to send
 * @param should_end_line `bool` Whether or not to end the line
 */
void print(float value, bool should_end_line = true);


/**
 * @brief Send a number to the terminal using `std::cout`
 * 
 * @param value `int` The text to send
 * @param should_end_line `bool` Whether or not to end the line
 */
void print(int value, bool should_end_line = true);


/**
 * @brief Combines all strings within `texts` into one string
 * and sends it to the terminal
 * 
 * @param texts `std::vector<std::string> Vector of texts
 * @param should_end_line `bool` Whether or not to end the line
 */
void print(std::vector<std::string> texts, bool should_end_line = true);


/**
 * @brief Combines a vector of strings into one string
 * 
 * @param texts `std::vector<std::string>` Vector of strings
 * @return `std::string` The combined strings
 */
std::string to_string(std::vector<std::string> texts);

/**
 * @brief `std::to_string` but keeps precision of primitive data types
 * 
 * @param data `double` Number to convert
 * @return `std::string` The converted string 
 */
std::string to_string(double data);


/**
 * @brief `std::to_string` but keeps precision of primitive data types
 * 
 * @param data `float` Number to convert
 * @return `std::string` The converted string 
 */
std::string to_string(float data);


/**
 * @brief `std::to_string` but keeps precision of primitive data types
 * 
 * @param data `int` Number to convert
 * @return `std::string` The converted string 
 */
std::string to_string(int data);


/**
 * @brief Gets user input as a string
 * 
 * @param prompt `std::string` Defaults to `""` The prompt to ask 
 * before getting user input
 * @return `status_utils::StatusedValue<std::string>` Returns `status_utils::StatusCode::FAILED` when the message is `exit`, `status_utils::StatusCode::OK` otherwise. 
 */
status_utils::StatusedValue<std::string> get_user_input_string(std::string prompt = "");


/**
 * @brief Gets user input as a double
 * 
 * @param prompt `std::string` Defaults to `Say Something!` The prompt to ask 
 * before getting user input
 * @param persistent `bool` Defaults to `false`, whether or not to 
 * keep on prompting or end with an error
 * @param error_message `std::string` Defaults to `Sorry, please try again:`
 * The error message to send 
 * @return `status_utils::StatusedValue<std::string>` Returns `status_utils::StatusCode::FAILED` when the message is `exit`, `status_utils::StatusCode::OK` otherwise. 
 */
status_utils::StatusedValue<double> get_user_input_double(
    std::string prompt = "", 
    bool persistent = false, 
    std::string error_message = "Sorry, please try again: ");


/**
 * @brief Gets user input as a float
 * 
 * @param prompt `std::string` Defaults to `` The prompt to ask 
 * before getting user input
 * @param persistent `bool` Defaults to `false`, whether or not to 
 * keep on prompting or end with an error
 * @param error_message `std::string` Defaults to `Sorry, please try again:`
 * The error message to send 
 * @return `status_utils::StatusedValue<std::string>` Returns `status_utils::StatusCode::FAILED` when the message is `exit`, `status_utils::StatusCode::OK` otherwise. 
 */
status_utils::StatusedValue<float> get_user_input_float(
    std::string prompt = "", 
    bool persistent = false, 
    std::string error_message = "Sorry, please try again: ");


/**
 * @brief Gets user input as a int
 * 
 * @param prompt `std::string` Defaults to `` The prompt to ask 
 * before getting user input
 * @param persistent `bool` Defaults to `false`, whether or not to 
 * keep on prompting or end with an error
 * @param error_message `std::string` Defaults to `Sorry, please try again:`
 * The error message to send 
 * @return `status_utils::StatusedValue<std::string>` Returns `status_utils::StatusCode::FAILED` when the message is `exit`, `status_utils::StatusCode::OK` otherwise. 
 */
status_utils::StatusedValue<int> get_user_input_int(
    std::string prompt = "", 
    bool persistent = false, 
    std::string error_message = "Sorry, please try again: ");

} // namespace util

#endif // UTIL_HPP