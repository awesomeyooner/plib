#ifndef MATH_HELPER_HPP
#define MATH_HELPER_HPP

#include <cmath>

namespace math{

    double clamp(double input, double min, double max){
        if(input < min && input < max)
            input = min;
        else if(input > min && input > max)
            input = max;

        return input;
    }

    int clamp(int input, int min, int max){
        if(input < min && input < max)
            input = min;
        else if(input > min && input > max)
            input = max;

        return input;
    }

} // namespace math

namespace conversions{

    static int width = 0;
    static int height = 0;

    double mg_to_mps2(double mg){
        return mg * 0.00980665;
    }

    double degrees_to_radians(double degrees){
        return (degrees / 180) * M_PI;
    }

    double cartesian_to_native_X(double x){
        return x + (width / 2);
    }

    double cartesian_to_native_Y(double y){
        return -y + (height / 2);
    }

    double native_to_cartesian_X(double x){
        return x - (width / 2);
    }

    double native_to_cartesian_Y(double y){
        return -y + (height / 2);
    }

} // namespace math_util

#endif // MATH_HELPER_HPP