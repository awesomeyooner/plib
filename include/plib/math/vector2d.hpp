#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP


#include "plib/math/n_vector.hpp"

#include <cmath>


class Vector2d : public Vector<2>
{

    public:

        /**
         * @brief Create a 2-Dimensional vector whose `x` and `y` values are
         * set to `default_values`
         * 
         * @param default_values `double = 0` 
         */
        Vector2d(double default_values = 0);

        /**
         * @brief Create a 2-Dimensional vector whose `x` and `y` values are equal
         * to the `list`
         * 
         * @param list `std::initializer_list<double>` The order is `{x, y}
         */
        Vector2d(std::initializer_list<double> list);

        /**
         * @brief Create a 2-Dimensional vector whose `x` and `y` values are equal
         * to the given ones
         * 
         * @param x `double`
         * @param y `double`
         */
        Vector2d(double x, double y);

        /**
         * @brief Apply a 2D rotation matrix with the given radians
         * 
         * Standard 2D rotation matrix
         * 
         * `V' = Rot Matrix * V`
         * 
         * ```
         * [ cos  -sin ]
         * [ sin  cos  ]
         * ```
         * 
         * @param radians `double`
         * @return `Vector2d` 
         */
        Vector2d rotate(double radians);

    private:


}; // class Vector2d


#endif // VECTOR2D_HPP