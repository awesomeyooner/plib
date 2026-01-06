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