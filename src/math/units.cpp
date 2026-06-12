#include "plib/math/units.hpp"


double units::to_radians(double degrees)
{
    return degrees * M_PI / 180;

} // end of "to_radians(double)"


double units::to_degrees(double radians)
{
    return radians * 180 / M_PI;

} // to_degrees(double)