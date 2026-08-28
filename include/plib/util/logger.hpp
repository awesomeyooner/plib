#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <filesystem>

#include "plib/util/system.hpp"
#include "plib/util/string_util.hpp"

class Logger{
    
    public:

        // Log file to write to
        static std::ofstream m_log_file;

        // bool controlling whether to write to the log file or not
        static bool m_should_write_to_file;

        // Initialize the log file
        static bool init(std::string extension = "log");

        // Log that Logger has been closed and close the log file
        static void close();

        /**
         * @brief Prints text to the terminal without newline
         * 
         * @param text `const std::string&`
         */
        static void print(const std::string& text);

        /**
         * @brief Prints text to the terminal with newline
         * 
         * @param text `const std::string&`
         */
        static void println(const std::string& text);

        /**
         * @brief Log the text with `INFO` as the header
         * 
         * @param text `std::string` The text to log
         */
        static void info(std::string text);

        /**
         * @brief Log the text with `INFO` as the header
         * 
         * @param texts `std::vector<std::string>` The texts to log
         */
        static void info(std::vector<std::string> texts);

        /**
         * @brief Log the text with `INFO` as the header
         * 
         * @param data `double` The text to log
         */
        static void info(double data);

        /**
         * @brief Log the text with `INFO` as the header
         * 
         * @param data `float` The text to log
         */
        static void info(float data);

        /**
         * @brief Log the text with `INFO` as the header
         * 
         * @param data `int` The text to log
         */
        static void info(int data);

        /**
         * @brief Log the text with `ERROR` as the header
         * 
         * @param text `std::string` The text to log
         */
        static void error(std::string text);

        /**
         * @brief Log the text with `ERROR` as the header
         * 
         * @param texts `std::vector<std::string>` The texts to log
         */
        static void error(std::vector<std::string> texts);

        /**
         * @brief Log the text with `ERROR` as the header
         * 
         * @param data `double` The text to log
         */
        static void error(double data);

        /**
         * @brief Log the text with `ERROR` as the header
         * 
         * @param data `float` The text to log
         */
        static void error(float data);

        /**
         * @brief Log the text with `ERROR` as the header
         * 
         * @param data `int` The text to data
         */
        static void error(int data);

        /**
         * @brief Log the text with `DEBUG` as the header
         * 
         * @param text `std::string` The text to log
         */
        static void debug(std::string text);
        
        /**
         * @brief Log the text with `DEBUG` as the header
         * 
         * @param texts `std::vector<std::string>` The texts to log
         */
        static void debug(std::vector<std::string> texts);

        /**
         * @brief Log the text with `DEBUG` as the header
         * 
         * @param data `double` The data to log
         */
        static void debug(double data);

        /**
         * @brief Log the text with `DEBUG` as the header
         * 
         * @param data `float` The data to log
         */
        static void debug(float data);

        /**
         * @brief Log the text with `DEBUG` as the header
         * 
         * @param data `int` The data to log
         */
        static void debug(int data);

        /**
         * @brief Log text with a header and a timestamp. Optionally, write to a log file
         * 
         * @param header `std::string` The header to display, in brackets `[HEADER]`
         * @param text `std::string` The text to log
         * @param write_to_file `bool` Whether or not to write to a log file
         */
        static void log(std::string header, std::string text, bool should_write_to_file = m_should_write_to_file);


        /**
         * @brief Log text with a header and a timestamp. Optionally, write to a log file
         * 
         * @param header `std::string` The header to display, in brackets `[HEADER]`
         * @param texts `std::vector<std::string>` Texts to log
         * @param write_to_file `bool` Whether or not to write to a log file
         */
        static void log(std::string header, std::vector<std::string> texts, bool should_write_to_file = m_should_write_to_file);

        /**
         * @brief Log text with a header and a timestamp. Optionally, write to a log file
         * 
         * @param header `std::string` The header to display, in brackets `[HEADER]`
         * @param data `double` Data to log
         * @param write_to_file `bool` Whether or not to write to a log file
         */
        static void log(std::string header, double data, bool should_write_to_file = m_should_write_to_file);

        /**
         * @brief Log text with a header and a timestamp. Optionally, write to a log file
         * 
         * @param header `std::string` The header to display, in brackets `[HEADER]`
         * @param data `float` Data to log
         * @param write_to_file `bool` Whether or not to write to a log file
         */
        static void log(std::string header, float data, bool should_write_to_file = m_should_write_to_file);

        /**
         * @brief Log text with a header and a timestamp. Optionally, write to a log file
         * 
         * @param header `std::string` The header to display, in brackets `[HEADER]`
         * @param data `int` Data to log
         * @param write_to_file `bool` Whether or not to write to a log file
         */
        static void log(std::string header, int data, bool should_write_to_file = m_should_write_to_file);

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
         * @brief Write a `double` to a logfile
         * 
         * @param value `double`
         */
        static void write_to_file(double value);

        /**
         * @brief Write multiple `std::string`'s to a log file with CSV format
         * 
         * @param values `std::vector<std::string> values`
         */
        static void write_csv(std::vector<std::string> values);

        /**
         * @brief Write multiple `double`'s to a log file with CSV format
         * 
         * @param values `std::vector<std::string> values`
         */
        static void write_csv(std::vector<double> values);

        /**
         * @brief Returns if `m_log_file` is initialized and if it is open
         * 
         * @return `bool` Whether or not the log file is initialzed and open
         */
        static bool is_file_ok();


    private:
       
}; // class Logger


#endif // LOGGER_HPP