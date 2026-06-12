#ifndef UNITS_HPP
#define UNITS_HPP


#include <cmath>


namespace units
{

    /**
     * @brief Converts degrees to radians
     * 
     * @param degrees `double`
     * @return `double` Radians
     */
    double to_radians(double degrees);

    /**
     * @brief Converts radians to degrees
     * 
     * @param radians `double`
     * @return `double` Degrees 
     */
    double to_degrees(double radians);

} // namespace units


#endif // UNITS_HPP
