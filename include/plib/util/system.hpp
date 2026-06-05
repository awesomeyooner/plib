#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>
#include <iostream>
#include <unistd.h>
#include <cstdint>
#include <unistd.h>
#include <thread>
#include <ctime>
#include <mutex>
#include <fstream>
#include <chrono>

#include "util.hpp"
#include "status.hpp"

class System{

    public:


        /**
         * @brief Initialzie the system. Sets the start time to whenever this is called
         * 
         */
        static void initialize();


        /**
         * @brief Returns the status of the system. Used to control while loops
         * 
         * @return `bool` True if alive, false if not
         */
        static bool is_alive();


        /**
         * @brief Sets keep_alive to false
         * 
         */
        static void shutdown();


        /**
         * @brief Gets the current timepoint as `std::chrono::_V2::system_clock::time_point`
         * 
         * @return `std::chrono::_V2::system_clock::time_point` The timepoint 
         */
        static std::chrono::_V2::system_clock::time_point get_timepoint();


        /**
         * @brief Gets the current time since epoch
         * 
         * @return `double` The time in seconds since epoch 
         */
        static double get_time();


        /**
         * @brief Converts `std::chrono::_V2::system_clock::time_point` to `double`
         * 
         * @param timepoint `std::chrono::_V2::system_clock::time_point` The timepoint to convert 
         * @return `double` The double representation of the timepoint
         */
        static double timepoint_to_double(std::chrono::_V2::system_clock::time_point timepoint);


        /**
         * @brief Gets the time difference between two `std::chrono::_V2::system_clock::time_point`
         * as a double
         * 
         * @param initial `std::chrono::_V2::system_clock::time_point` The initial timepoint
         * @param final `std::chrono::_V2::system_clock::time_point` The final timepoint
         * @return `double` The time difference as a double 
         */
        static double get_time_difference(
            std::chrono::_V2::system_clock::time_point initial, 
            std::chrono::_V2::system_clock::time_point final);


        /**
         * @brief Returns the current time since epoch
         * 
         * @return `double` Time since epoch in `seconds`
         */
        static double get_epoch();


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

        // Flag to keep any threads or main programs alive
        static bool m_keep_alive;

        // The starting timepoint to know where 0 seconds is
        static std::chrono::_V2::system_clock::time_point m_start;

}; // class System

#endif // SYSTEM_HPP