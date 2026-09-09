#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include <vector>
#include <iostream>
#include <deque>
#include <cmath>

#include "plib/util/system.hpp"
#include "plib/util/logger.hpp"
#include "plib/util/stamped_value.hpp"


// Options for what Feed Forward method to use
enum class FeedForwardType{
    
    // Applies a constant feedforward, regardless of direction
    STATIC,

    // Applies a constant feedforward based on the direction / sign of error
    STATIC_SIGNED,

    // Applies a feedforward based on the cosine of the position (position must be in radians)
    COS,

    // Applies a feedforward based on the sine of the position (position must be in radians)
    SIN

}; // enum FeedForwardType


// Class for a PID Controller, implementing feedforwards in addition to PID.
class PIDController{

    public:

        // Proportional Gain
        double m_kP = 0;
        
        // Integral Gain
        double m_kI = 0;
        
        // Derivative Gain
        double m_kD = 0;

        // Static Feedforward Gain. Type is determined by `m_ff_type`
        double m_kF = 0;

        // Velocity Feedforward Gain. This is proportional to the setpoint
        double m_kV = 0;

        // The type of feedforward to use
        FeedForwardType m_ff_type = FeedForwardType::STATIC_SIGNED;

        // How much time between the current and last integrated value to use
        double m_integral_time_bound = 5; // seconds

        // The setpoint to go towards
        double m_setpoint = 0;

        // The current position
        double m_position = 0;

        // The current velocity
        double m_velocity = 0;

        // The timestamp since the last time `calculate` was called
        double m_prev_timestamp = 0;

        PIDController(double kP = 0, double kI = 0, double kD = 0);
        PIDController(double kP = 0, double kI = 0, double kD = 0, double kF = 0, FeedForwardType ff_type = FeedForwardType::STATIC_SIGNED);

        double get_error();
        double get_accumulated_error();
        double get_error_rate();

        double calculate(double timestamp, double position);
        double calculate(double timestamp, double position, double setpoint);
        double calculate(double timestamp, double position, double velocity, double setpoint);

    private:

        // Buffer for storing previous loops' errors
        // The front has the MOST RECENT error
        // The back has the OLDEST error
        std::deque<StampedValue<double>> m_error_buffer;
        
        // The accumulated error (integral of error within the bounds)
        double m_accumulated_error;

        double update_accumulated_error(double timestamp, double position);
        double update_error_rate(double timestamp, double position);
        double get_static_feedforward();
        double get_velocity_feedforward(double setpoint);


}; // class PIDController

#endif // PID_CONTROLLER_HPP