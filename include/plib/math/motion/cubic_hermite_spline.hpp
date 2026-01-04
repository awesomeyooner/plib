#ifndef CUBIC_HERMITE_SPLINE_HPP
#define CUBIC_HERMITE_SPLINE_HPP

#include <cmath>

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


    private:

}; // class CubicHermiteSpline


#endif // CUBIC_HERMITE_SPLINE_HPP