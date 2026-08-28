#include "plib/util/logger.hpp"


using namespace string_util;
using namespace std;

namespace fs = std::filesystem;


std::ofstream Logger::m_log_file;
bool Logger::m_should_write_to_file = false;


bool Logger::init(std::string extension)
{
    // `YEAR-MONTH-DAY_HOUR_MIN_SEC
    std::string datetime = System::get_date_time("-", "_");
    std::string filename = "log_" + datetime + "." + extension;

    // If the /logs directory does not exist
    // Then create it
    if(!fs::is_directory("../logs/"))
        fs::create_directory("../logs/");

    m_log_file.open("../logs/" + filename);

    if(is_file_ok())
    {
        info("Program Started!");
        return true;
    } 
    else
    {
        error("Failed to create .log file!");
        return false;
    }

} // end of "initialize(std::string filename)"


void Logger::close()
{
    // if the file isn't being used, then don't do anything
    if(!is_file_ok())
    {
        return;
    }

    // Log that the program has ended and close the file
    info("Program Ended!");
    m_log_file.close();

} // end of "close"


void Logger::print(const std::string& text)
{
    std::cout << text;

} // end of "print(const std::string& text)"


void Logger::println(const std::string& text)
{
    std::cout << text << std::endl;

} // end of "println(const std::string& text)"


void Logger::info(std::string text)
{
    // Log the text using `INFO` as the header
    log("INFO", text, m_should_write_to_file);

} // end of "info"


void Logger::info(std::vector<std::string> texts)
{
    // Log the text using `INFO` as the header
    log("INFO", texts, m_should_write_to_file);

} // end of "info"


void Logger::info(double data)
{
    // Log the text using `INFO` as the header
    log("INFO", data, m_should_write_to_file);
    
} // end of "info"


void Logger::info(float data)
{
    // Log the text using `INFO` as the header
    log("INFO", data, m_should_write_to_file);
    
} // end of "info"


void Logger::info(int data)
{
    // Log the text using `INFO` as the header
    log("INFO", data, m_should_write_to_file);
    
} // end of "info"


void Logger::error(std::string text)
{
    // Log the text using `ERROR` as the header
    log("ERROR", text, m_should_write_to_file);
    
} // end of "error"


void Logger::error(std::vector<std::string> texts)
{
    // Log the text using `DEBUG` as the header
    log("ERROR", texts, m_should_write_to_file);

} // end of "error"


void Logger::error(double data)
{
    // Log the text using `ERROR` as the header
    log("ERROR", data, m_should_write_to_file);

} // end of "ERROR"


void Logger::error(float data)
{
    // Log the text using `ERROR` as the header
    log("ERROR", data, m_should_write_to_file);

} // end of "ERROR"


void Logger::error(int data)
{
    // Log the text using `ERROR` as the header
    log("ERROR", data, m_should_write_to_file);

} // end of "ERROR"


void Logger::debug(std::string text)
{
    // Log the text using `DEBUG` as the header
    log("DEBUG", text, m_should_write_to_file);

} // end of "debug"


void Logger::debug(std::vector<std::string> texts)
{
    // Log the text using `DEBUG` as the header
    log("DEBUG", texts, m_should_write_to_file);

} // end of "debug"


void Logger::debug(double data)
{
    // Log the text using `DEBUG` as the header
    log("DEBUG", data, m_should_write_to_file);

} // end of "debug"


void Logger::debug(float data)
{
    // Log the text using `DEBUG` as the header
    log("DEBUG", data, m_should_write_to_file);

} // end of "debug"


void Logger::debug(int data)
{
    // Log the text using `DEBUG` as the header
    log("DEBUG", data, m_should_write_to_file);

} // end of "debug"


void Logger::log(std::string header, std::string text, bool should_write_to_file)
{
    // Store the formatted text in this variable
    std::string formatted = format_text(header, text);

    // Write to the file if `m_should_write_to_file` is true
    if(should_write_to_file)
    {
        write_to_file(formatted);
    }

    // Send the formatted text to the terminal
    std::cout << formatted << std::endl;

} // end of "log"


void Logger::log(std::string header, std::vector<std::string> texts, bool should_write_to_file)
{
    // Combine the strings into one
    std::string combined = util::to_string(texts);

    log(header, combined, should_write_to_file);

} // end of "log"


void Logger::log(std::string header, double data, bool should_write_to_file)
{
    log(header, util::to_string(data), should_write_to_file);

} // end of "log"


void Logger::log(std::string header, float data, bool should_write_to_file)
{
    log(header, util::to_string(data), should_write_to_file);

} // end of "log"


void Logger::log(std::string header, int data, bool should_write_to_file)
{
    log(header, util::to_string(data), should_write_to_file);

} // end of "log"


std::string Logger::format_text(std::string header, std::string text)
{
    // Create datetime string using `:` as unit seperator and just a space as a gap
    // std::string datetime = System::get_date_time(":", " ");

    // [ HEADER ] + text
    // std::string formatted = datetime + " [ " + header + " ] " + text;

    // Return the formatted text
    return timestamped_header(header, text);

} // end of "format_text"


void Logger::write_to_file(std::string text)
{
    // If the logfile initialized nor open, then don't do anything
    if(!is_file_ok())
    {
        return;
    }

    // Write text to the log file
    m_log_file << text << std::endl;

} // end of "write_to_file"


void Logger::write_to_file(double value)
{
    write_to_file(std::to_string(value));

} // end of "write_to_file(double)"


void Logger::write_csv(std::vector<std::string> values)
{
    std::string total = "";

    for(int i = 0; i < values.size(); i++)
    {
        std::string value = values.at(i);

        total += value;

        // If this is NOT the last index
        // Then add the comma
        if(i != values.size() - 1)
            total += ",";
    }

    write_to_file(total);

} // end of "write_csv(std::vector<std::string>)"


void Logger::write_csv(std::vector<double> values)
{
    std::string total = "";

    for(int i = 0; i < values.size(); i++)
    {
        std::string value = std::to_string(values.at(i));

        total += value;

        // If this is NOT the last index
        // Then add the comma
        if(i != values.size() - 1)
            total += ",";
    }

    write_to_file(total);

} // end of "write_csv(std::vector<double>)"


bool Logger::is_file_ok()
{
    // True if the log file is initialized and is open
    return m_log_file && m_log_file.is_open();

} // end of "is_file_ok"