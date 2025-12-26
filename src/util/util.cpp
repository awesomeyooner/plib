#include "plib/util/util.hpp"

namespace util{

void print(std::string text, bool should_end_line)
{
    // If it should end line, send std::endl
    if(should_end_line)
    {
        std::cout << text << std::endl;
    }
    else{
        std::cout << text;
    }

} // end of "print"


void print(std::vector<std::string> texts, bool should_end_line)
{
    // Store the combined texts into this variable
    std::string combined = "";

    // Loop through every single string and add it to combined
    for(std::string text : texts)
    {
        combined += text;
    }

    // Print out the combined string
    print(combined, should_end_line);

} // end of "print"


std::string to_string(double data)
{
    std::stringstream stream;

    // Convert using the most digits possible (10)
    stream << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10) << data;

    return stream.str();   

} // end of "to_string"


std::string to_string(float data)
{
    std::stringstream stream;

    stream << std::fixed << std::setprecision(std::numeric_limits<float>::max_digits10) << data;

    return stream.str();   

} // end of "to_string"


std::string to_string(int data)
{
    std::stringstream stream;

    stream << std::fixed << std::setprecision(std::numeric_limits<int>::max_digits10) << data;

    return stream.str();   

} // end of "to_string"


status_utils::StatusedValue<std::string> get_user_input_string(std::string prompt)
{
    // Store the input in this variable
    std::string buffer;

    // Error code for if this method worked
    status_utils::StatusCode status;

    // Prompt the user
    print(prompt, false);

    // Get the user input and store it in buffer
    std::getline(std::cin, buffer);

    // If it's exit, then return FAILED, if not, return OK
    if(buffer == "exit")
        status = status_utils::StatusCode::FAILED;
    else
        status = status_utils::StatusCode::OK;

    return status_utils::StatusedValue<std::string>(buffer, status);

} // end of "get_user_input_string"


status_utils::StatusedValue<double> get_user_input_double(
    std::string prompt, 
    bool persistent, 
    std::string error_message)
{
    // Get the user input as a string first
    status_utils::StatusedValue<std::string> user_input = get_user_input_string(prompt);

    // If the user said "exit" then return FAILED to indicated exit
    if(user_input.status == status_utils::StatusCode::FAILED)
    {
        return status_utils::StatusedValue<double>(0, status_utils::StatusCode::FAILED);
    }

    // Store the value of the input into this variable
    double value;

    // if persistent is true, keep on asking until the user enters a valid number
    while(true)
    {
        try
        {
            // Try to convert the string to a double
            value = std::stod(user_input.value);

            // if it works, return it
            return status_utils::StatusedValue<double>(value, status_utils::StatusCode::OK);
        }
        catch(const std::exception& e)
        {
            // If not persistent, then just return ERROR
            if(!persistent)
            {
                return status_utils::StatusedValue<double>(0, status_utils::StatusCode::ERROR);
            }

            // Print the error message if persistent and refresh the user input
            print(error_message, false);
            user_input = get_user_input_string();
        }
    }

    throw std::runtime_error("Error calling 'get_user_input_double'");
} // end of "get_user_input_double"


status_utils::StatusedValue<float> get_user_input_float(
    std::string prompt, 
    bool persistent, 
    std::string error_message)
{
    // Get the user input as a string first
    status_utils::StatusedValue<std::string> user_input = get_user_input_string(prompt);

    // If the user said "exit" then return FAILED to indicated exit
    if(user_input.status == status_utils::StatusCode::FAILED)
    {
        return status_utils::StatusedValue<float>(0, status_utils::StatusCode::FAILED);
    }

    // Store the value of the input into this variable
    double value;

    // if persistent is true, keep on asking until the user enters a valid number
    while(true)
    {
        try
        {
            // Try to convert the string to a double
            value = std::stod(user_input.value);

            // if it works, return it
            return status_utils::StatusedValue<float>(value, status_utils::StatusCode::OK);
        }
        catch(const std::exception& e)
        {
            // If not persistent, then just return ERROR
            if(!persistent)
            {
                return status_utils::StatusedValue<float>(0, status_utils::StatusCode::ERROR);
            }

            // Print the error message if persistent and refresh the user input
            print(error_message, false);
            user_input = get_user_input_string();
        }
    }

    throw std::runtime_error("Error calling 'get_user_input_float'");
} // end of "get_user_input_float"


status_utils::StatusedValue<int> get_user_input_int(
    std::string prompt, 
    bool persistent, 
    std::string error_message)
{
    // Get the user input as a string first
    status_utils::StatusedValue<std::string> user_input = get_user_input_string(prompt);

    // If the user said "exit" then return FAILED to indicated exit
    if(user_input.status == status_utils::StatusCode::FAILED)
    {
        return status_utils::StatusedValue<int>(0, status_utils::StatusCode::FAILED);
    }

    // Store the value of the input into this variable
    double value;

    // if persistent is true, keep on asking until the user enters a valid number
    while(true)
    {
        try
        {
            // Try to convert the string to a double
            value = std::stod(user_input.value);

            // if it works, return it
            return status_utils::StatusedValue<int>(value, status_utils::StatusCode::OK);
        }
        catch(const std::exception& e)
        {
            // If not persistent, then just return ERROR
            if(!persistent)
            {
                return status_utils::StatusedValue<int>(0, status_utils::StatusCode::ERROR);
            }

            // Print the error message if persistent and refresh the user input
            print(error_message, false);
            user_input = get_user_input_string();
        }
    }

    throw std::runtime_error("Error calling 'get_user_input_int'");
} // end of "get_user_input_int"


} // namespace util