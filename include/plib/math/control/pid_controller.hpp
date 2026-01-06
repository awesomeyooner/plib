#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include <vector>

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

class PIDController{

    public:

        // Proportional Gain
        double m_kP;
        
        // Integral Gain
        double m_kI;
        
        // Derivative Gain
        double m_kD;

        // Feedforward Gain. Type is determined by `m_feedforward_type`
        double m_kF;

        // The setpoint to go towards
        double m_setpoint;

        // The current position
        double m_position;

        // The current velocity
        double m_velocity;

        // The accumulated error buffer
        std::vector<double> accumulated_error;

        // The timestamp of the previous loop
        double m_previous_timestamp;

        double get_error(double setpoint);
        double get_accumulated_error();
        double get_error_rate(double setpoint);

        double calculate(double position);
        double calculate(double position, double setpoint);
        double calculate(double position, double setpoint, double velocity);

    private:



}; // class PIDController

#endif // PID_CONTROLLER_HPP