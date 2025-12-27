#include "plib/util/logger.hpp"

std::ofstream Logger::m_log_file;
bool Logger::m_should_write_to_file = false;


bool Logger::initialize()
{
    std::string datetime = System::get_date_time("-", "_");
    std::string file_name = "log_" + datetime + ".log";
    m_log_file.open("../logs/" + file_name);

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

} // end of "initialize"


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


void Logger::info(std::string text)
{
    // Log the text using `INFO` as the header
    log("INFO", text, m_should_write_to_file);

} // end of "info"


void Logger::error(std::string text)
{
    // Log the text using `ERROR` as the header
    log("ERROR", text, m_should_write_to_file);
} // end of "error"


void Logger::debug(std::string text)
{
    // Log the text using `DEBUG` as the header
    log("DEBUG", text, m_should_write_to_file);
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


std::string Logger::format_text(std::string header, std::string text)
{
    // Create datetime string using `:` as unit seperator and just a space as a gap
    std::string datetime = System::get_date_time(":", " ");

    // [HEADER] + text
    std::string formatted = datetime + " [" + header + "] " + text;

    // Return the formatted text
    return formatted;

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


bool Logger::is_file_ok()
{
    // True if the log file is initialized and is open
    return m_log_file && m_log_file.is_open();

} // end of "is_file_ok"