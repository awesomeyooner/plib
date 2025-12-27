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
    return get_time_difference(m_start, get_timepoint());

} // end of "get_time_since_start"