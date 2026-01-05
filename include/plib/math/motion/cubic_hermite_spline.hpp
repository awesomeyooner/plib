#ifndef CUBIC_HERMITE_SPLINE_HPP
#define CUBIC_HERMITE_SPLINE_HPP

#include <cmath>

#include "plib/util/logger.hpp"

class CubicHermiteSpline{


    public:
        double m_P0;
        double m_v0;
        double m_P1;
        double m_v1;

        double m_a_max;
        double m_v_max;

        double k;

        CubicHermiteSpline();


        /**
         * @brief Get k when acceleration is limited
         * 
         * @return `double` k 
         */
        double get_ka();

        /**
         * @brief Get k when velocity is limited
         * 
         * @return `double` k 
         */
        double get_kv();

        /**
         * @brief Get k, compares ka and kv and returns the smaller one
         * 
         * @return `double` k 
         */
        double get_k();


        /**
         * @brief Get the total time the spline would take. It's just 1 / k
         * 
         * @return `double` The time in seconds 
         */
        double get_total_time();


        /**
         * @brief The Spline as a function of t
         * 
         * @param t `double` The time from [0, 1/k] 
         * @return `double` The output of the function 
         */
        double P(double t);


    private:

}; // class CubicHermiteSpline


#endif // CUBIC_HERMITE_SPLINE_HPP