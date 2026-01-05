#ifndef CUBIC_HERMITE_SPLINE_HPP
#define CUBIC_HERMITE_SPLINE_HPP

#include <cmath>

#include "plib/util/logger.hpp"

class CubicHermiteSpline{


    public:

        // Initial and End Conditions

            // Initial Position
            double m_P0;

            // Initial Velocity
            double m_v0;

            // End Position
            double m_P1;

            // End Velocity
            double m_v1;

        // Constraints

            // The max allowed jerk
            double m_j_max;

            // The max allowed acceleration
            double m_a_max;

            // The max allowed velocity
            double m_v_max;

        double k;

        CubicHermiteSpline();


        /**
         * @brief Get k when jerk is limited
         * 
         * @return `double` k 
         */
        double get_kj();

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

        // TODO: Move the nonzero_min functions to math_helper.hpp once you rewrite it to define and declare
        
        /**
         * @brief Returns the smaller of the two parameters, but if one is zero, it'll return the other.
         * 
         * @param a `double` The first number
         * @param b `double` The second number
         * @return `double` The smaller of the two excluding 0 
         */
        static double nonzero_min(double a, double b);

        /**
         * @brief Returns the smaller of the three parameters, but if one is zero, it'll return the other.
         * 
         * @param a `double` The first number
         * @param b `double` The second number
         * @param c `double` The third number
         * @return `double` The smaller of the three excluding 0 
         */
        static double nonzero_min(double a, double b, double c);

}; // class CubicHermiteSpline


#endif // CUBIC_HERMITE_SPLINE_HPP