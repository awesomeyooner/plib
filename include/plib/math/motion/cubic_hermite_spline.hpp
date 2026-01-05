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
         * @return `double` The position of the spline 
         */
        double P(double t);


        /**
         * @brief The 1st derivative (velocity) of P
         * 
         * @param t `double` The time from [0, 1/k] 
         * @return `double` The velocity of the spline
         */
        double P_prime_1(double t);


        /**
         * @brief The 2nd derivative (acceleration) of P
         * 
         * @param t `double` The time from [0, 1/k] 
         * @return `double` The acceleration of the spline
         */
        double P_prime_2(double t);


        /**
         * @brief The 3rd derivative (jerk) of P
         * 
         * @param t `double` The time from [0, 1/k] 
         * @return `double` The jerk of the spline
         */
        double P_prime_3(double t);

    private:

}; // class CubicHermiteSpline


#endif // CUBIC_HERMITE_SPLINE_HPP