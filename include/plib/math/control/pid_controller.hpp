#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include <vector>
#include <iostream>

#include "plib/util/system.hpp"

// Options for what Feed Forward method to use
enum class FeedForwardType{
    
    // Applies a constant feedforward, regardless of direction
    STATIC,

    // Applies a constant feedforward based on the direction / sign of error
    BI_STATIC,

    // Applies a feedforward based on the cosine of the position (position must be in radians)
    COS,

    // Applies a feedforward based on the sine of the position (position must be in radians)
    SIN

}; // enum FeedForwardType


// Struct for a value to be shared with its timestamp since it was updated / created

template <typename T>
struct TimestampedValue{
    
    T m_value;
    double m_timestamp;

    TimestampedValue(T value, double timestamp)
    {
        update(value, timestamp);

    } // end of TimestampedValue

    TimestampedValue(T value)
    {
        update(value);

    } // end of TimestampedValue

    // One-liner for updating the values
    void update(T value, double timestamp)
    {
        m_value = value;
        m_timestamp = timestamp

    } // end of update

    // Updates the value and auto refreshes the timestamp
    void update(T value)
    {
        // Get the current time
        double time = System::get_time_since_start();
        update(value, time);

    } // end of "update"

}; // struct TimestampedValue

// Class for a PID Controller, implementing feedforwards in addition to PID.
class PIDController{

    public:

        // Proportional Gain
        double m_kP;
        
        // Integral Gain
        double m_kI;
        
        // Derivative Gain
        double m_kD;

        // Feedforward Gain. Type is determined by `m_ff_type`
        double m_kF;

        // The type of feedforward to use
        FeedForwardType m_ff_type;

        // The setpoint to go towards
        double m_setpoint;

        // The current position
        double m_position;

        // The current velocity
        double m_velocity;

        // The accumulated error buffer
        std::vector<double> error_buffer;

        // How much time between the current and last integrated value to use
        double integral_time_bound;

        // The timestamp of the previous loop
        double m_previous_timestamp;

        PIDController(double kP, double kI, double kD);
        PIDController(double kP, double kI, double kD, double kF, FeedForwardType ff_type);

        double get_error(double setpoint);
        double get_accumulated_error();
        double get_error_rate(double setpoint);

        double calculate(double position);
        double calculate(double position, double setpoint);
        double calculate(double position, double setpoint, double velocity);

    private:
        
        double accumulated_error;


}; // class PIDController

#endif // PID_CONTROLLER_HPP