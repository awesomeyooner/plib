#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

class Logger{
    
    public:

        // Log file to write to
        static std::ofstream m_log_file;

        // bool controlling whether to write to the log file or not
        static bool m_should_write_to_file;

        // Initialize the log file
        static bool initialize();

        // Log that Logger has been closed and close the log file
        static void close();

        /**
         * @brief Log the text with `INFO` as the header
         * 
         * @param text `std::string` The text to log
         */
        static void info(std::string text);

        /**
         * @brief Log the text with `ERROR` as the header
         * 
         * @param text `std::string` The text to log
         */
        static void error(std::string text);

        /**
         * @brief Log the text with `DEBUG` as the header
         * 
         * @param text `std::string` The text to log
         */
        static void debug(std::string text);

        /**
         * @brief Log text with a header and a timestamp. Optionally, write to a log file
         * 
         * @param header `std::string` The header to display, in brackets `[HEADER]`
         * @param text `std::string` The text to log
         * @param write_to_file `bool` Whether or not to write to a log file
         */
        static void log(std::string header, std::string text, bool should_write_to_file = m_should_write_to_file);

        /**
         * @brief Format text such that the current datetime is displayed first, then 
         * the header, and finally the text
         * @param header `std::string` The header to use
         * @param text `std::string` The text to display
         * @return `std::string` The formatted string 
         */
        static std::string format_text(std::string header, std::string text);

        /**
         * @brief Write an `std::string` to a logfile
         * 
         * @param text `std::string` The text to write
         */
        static void write_to_file(std::string text);

        /**
         * @brief Returns if `m_log_file` is initialized and if it is open
         * 
         * @return `bool` Whether or not the log file is initialzed and open
         */
        static bool is_file_ok();

        /**
         * @brief Get a formatted string of the current date and time in the following order: year, month
         * , day, hour, min, sec
         * 
         * @param unit_seperator `std::string` The string to use between each unit, like betweent the year, month, and day 
         * @param gap `std::string` The string to use between the calender date and clock time
         * @return `std::string` The formatted date and time string 
         */
        static std::string get_date_time(std::string unit_seperator = ":", std::string gap = "_");

        /**
         * @brief Gets the datetime object
         * 
         * @return `tm*` The datetime object 
         */
        static tm* get_tm();

    private:
       
}; // class Logger


#endif // LOGGER_HPP