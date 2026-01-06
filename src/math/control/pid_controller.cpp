#include "plib/math/control/pid_controller.hpp"

PIDController::PIDController(double kP, double kI, double kD, double kF, FeedForwardType ff_type)
{
    m_kP = kP;
    m_kI = kI;
    m_kD = kD;
    m_kF = kF;
    m_ff_type = ff_type;


} // end of "PIDController"


PIDController::PIDController(double kP, double kI, double kD) : PIDController(kP, kI, kD, 0, FeedForwardType::STATIC){}


double PIDController::get_error()
{
    // Using the sign convention of 
    // if a positive output gives an increase in position
    return m_setpoint - m_position;

} // end of "get_error"


double PIDController::get_accumulated_error()
{
    return m_accumulated_error;

} // end of "get_accumulated_error"


double PIDController::get_error_rate()
{
    return -m_velocity;

} // end of "get_error_rate"


double PIDController::calculate(double timestamp, double position)
{
    // Call the overload function with m_setpoint passed in as the setpoint
    return calculate(timestamp, position, m_setpoint);

} // end of "calculate"


double PIDController::calculate(double timestamp, double position, double setpoint)
{
    // Update the setpoint
    m_setpoint = setpoint;

    // Update the states
    m_position = position;

    // Update the error area and velocity approximations
    update_accumulated_error(timestamp, position);
    update_error_rate(timestamp, position);

    // Get the errors and feedforward
    double error = get_error();
    double error_rate = get_error_rate();
    double accumulated_error = get_accumulated_error();
    double feedforward = get_feedforward();

    // PID(F) Equation
    double output = (m_kP * error) + (m_kI * accumulated_error) + (m_kD * error_rate) + feedforward;

    return output;

} // end of "calculate"


double PIDController::calculate(double timestamp, double position, double velocity, double setpoint)
{
    // Update the setpoint
    m_setpoint = setpoint;

    // Update the states
    m_position = position;
    m_velocity = velocity;

    // Update the error area
    update_accumulated_error(timestamp, position);

    // Get the errors and feedforward
    double error = get_error();
    double error_rate = get_error_rate();
    double accumulated_error = get_accumulated_error();
    double feedforward = get_feedforward();

    // PID(F) Equation
    double output = (m_kP * error) + (m_kI * accumulated_error) + (m_kD * error_rate) + feedforward;

    return output;

} // end of "calculate"


// Use the sliding window technique to calculate the area
double PIDController::update_accumulated_error(double timestamp, double position)
{
    // Update the position
    m_position = position;

    // Calculate the error
    double error = get_error();

    // Refresh the error buffer
    m_error_buffer.push_front(TimestampedValue(error, timestamp));

    // If the error buffer has less than 2 elements, then there's no area yet
    if(m_error_buffer.size() < 2)
        return 0;

    // 0 is the newest, so 1 would be the second newest aka previous
    TimestampedValue<double> previous_error = m_error_buffer.at(1);

    // Calculate the difference in time between now and the previous error
    double delta_time = timestamp - previous_error.m_timestamp; 

    // Calculate the area using trapezoidal rule
    double area = ( previous_error.m_value + error ) * ( delta_time / 2 );

    // Add this loop's area to the accumulated error
    m_accumulated_error += area;

    // Remove all stale / old data
    for(size_t i = 0; i < m_error_buffer.size(); i++)
    { 
        // If the last most error is older than the allowed bounds, subtract it from
        // the accumulated error and remove it from the buffer
        if (m_error_buffer.back().m_timestamp < timestamp - m_integral_time_bound)
        {
            // Subtract the oldest error area from the accumulated error
            TimestampedValue<double> last_most = m_error_buffer.back();
            TimestampedValue<double> second_last_most = m_error_buffer.at(m_error_buffer.size() - 2); // -1 is the back, so -2 is the one before the back

            double dt = second_last_most.m_timestamp - last_most.m_timestamp;
            double remove_area = ( last_most.m_value + second_last_most.m_value ) * ( dt / 2);

            m_accumulated_error -= remove_area;

            // Remove it from the buffer
            m_error_buffer.pop_back();
        }
        // Once the back is within the bounds, stop the loop
        else
            break;
    }
    
    return m_accumulated_error;

} // end of "update_accumulated_error"


double PIDController::update_error_rate(double timestamp, double position)
{
    m_position = position;

    // If the error buffer has less than 2 elements, then there's no slope yet
    if(m_error_buffer.size() < 2)
        return 0;

    // 0 is the newest, so 1 would be the second newest aka previous
    TimestampedValue<double> previous_error = m_error_buffer.at(1);

    double error = get_error();

    // Calculate the slope and return it;
    double d_error = error - previous_error.m_value;
    double d_t = timestamp - previous_error.m_timestamp;

    double slope = d_error / d_t;

    m_velocity = -slope;

    return slope;

} // end of "update_error_rate"


double PIDController::get_feedforward()
{
    // Return the correspodning values based on the type
    switch(m_ff_type)
    {
        // Constant effort
        case FeedForwardType::STATIC:
            return m_kF;
        
        // Constant, but the direction of effort is based on sign of error 
        case FeedForwardType::STATIC_SIGNED:
            return std::copysign(m_kF, get_error());

        // Effort is the gain times the cos of position
        case FeedForwardType::COS:
            return m_kF * std::cos(m_position);

        // Effort is the gain times the sin of position
        case FeedForwardType::SIN:
            return m_kF * std::cos(m_position);

        // Default to no effort
        default:
            return 0;
    }

} // end of "get_feedforward"