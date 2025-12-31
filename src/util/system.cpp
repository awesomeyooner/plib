#include "plib/util/system.hpp"

void System::initialize()
{
    // Set the start time to now
    m_start = std::chrono::high_resolution_clock::now();

} // end of "initialize"


bool System::is_alive()
{
    return m_keep_alive;

} // end of "is_alive"


void System::shutdown()
{
    m_keep_alive = false;

} // end of "shutdown"


std::chrono::_V2::system_clock::time_point System::get_timepoint()
{
    return std::chrono::high_resolution_clock::now();

} // end of "get_timepoint"


double System::timepoint_to_double(std::chrono::_V2::system_clock::time_point timepoint)
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(timepoint.time_since_epoch()).count();

} // end of "timepoint_to_double"


double System::get_time_difference(
    std::chrono::_V2::system_clock::time_point initial,
    std::chrono::_V2::system_clock::time_point final)
{
    // Return the time difference 
    return std::chrono::duration_cast<std::chrono::duration<double>>(initial - final).count();

} // end of "get_time_difference"


double System::get_time_since_start()
{
    return get_time_difference(get_timepoint(), m_start);

} // end of "get_time_since_start"


std::string System::get_date_time(std::string unit_seperator, std::string gap)
{
    // Get the tm* object for the datetime data
    tm* datetime = get_tm();

    // Add 1900 years, I'm not sure why that is though
    std::string year = std::to_string(datetime->tm_year + 1900);
    
    // If the number is single digits, then add a 0 to make it take up two characters for formatting
    std::string month = datetime->tm_mon < 10 ? "0" + std::to_string(datetime->tm_mon) : std::to_string(datetime->tm_mon);
    std::string day = datetime->tm_mday < 10 ? "0" + std::to_string(datetime->tm_mday) : std::to_string(datetime->tm_mday);

    std::string hour = datetime->tm_hour < 10 ? "0" + std::to_string(datetime->tm_hour) : std::to_string(datetime->tm_hour);
    std::string min = datetime->tm_min < 10 ? "0" + std::to_string(datetime->tm_min) : std::to_string(datetime->tm_min);
    std::string sec = datetime->tm_sec < 10 ? "0" + std::to_string(datetime->tm_sec) : std::to_string(datetime->tm_sec);

    std::string all = year + unit_seperator + month + unit_seperator + day + gap + hour + unit_seperator + min + unit_seperator + sec;

    return all;
    
} // end of "get_date_time"


tm* System::get_tm()
{
    time_t time = std::time(NULL);

    tm* datetime = localtime(&time);

    return datetime;
} // end of "get_tm"


bool System::m_keep_alive = true;
std::chrono::_V2::system_clock::time_point System::m_start = System::get_timepoint();