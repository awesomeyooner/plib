#ifndef N_VECTOR_HPP
#define N_VECTOR_HPP


#include <vector>
#include <initializer_list>
#include <cmath>
#include <string>

template <int N>
class Vector
{

    public:

        /**
         * @brief Creates a new N-dimensional vector initialized with default values
         * 
         * @param default_values `double` The default value to set for all elements
         */
        Vector(double default_values = 0);

        /**
         * @brief Create a new N-dimensional vector with whose size and values are given
         * with the initialized list.
         * 
         * Example:
         * 
         * ```cpp
         * Vector<3> vec3 = {1, 2, 3};
         * ```
         * 
         * @param list `std::initializer_list` A list in the form of `{1, 2, 3}` 
         */
        Vector(std::initializer_list<double> list);

        /**
         * @brief Create a new N-dimensional vector whose size and values are given
         * by the `std::vector`
         * 
         * @param values `std::vector<double>`
         */
        Vector(std::vector<double> values);

        /**
         * @brief Creates a new N-dimensional vector using the values of the given vector.
         * This is a copy.
         * 
         * @param other `const Vector<N>& other
         */
        Vector(const Vector<N>& other);

        /**
         * @brief Creates a copy of the current vector.
         * 
         * @return `Vector<N>` 
         */
        Vector<N> copy();

        /**
         * @brief Get magnitude of the vector. This follows the textbook definition of magnitude,
         * 
         * `mag = sqrt( vec * vec )`
         * 
         * @return `double` 
         */
        double get_magnitude();

        /**
         * @brief Resize the vector to have a given magnitude but maintain same direction
         * 
         * This simply multiplies the unit vector by `magnitude`
         * 
         * @param magnitude `double`
         * @return `Vector<N>` 
         */
        Vector<N> with_magnitude(double magnitude);

        /**
         * @brief Get the unit vector whose magnitude is 1
         * 
         * @return `Vector<N>` 
         */
        Vector<N> get_unit_vector();

        /**
         * @brief Get the dimensions, aka size, of this vector
         * 
         * @return `int` 
         */
        int get_dimension();

        /**
         * @brief Gets a reference to the specific index
         * 
         * @param index `int`
         * @return `double&` 
         */
        double& at(int index);

        /**
         * @brief Get a const value of the given index
         * 
         * @param index `int` 
         * @return `double` 
         */
        double get(int index) const;

        /**
         * @brief Set the value at the given index
         * 
         * @param value `double` New value to set
         * @param index `int`
         */
        void set(double value, int index);

        /**
         * @brief Multiply a given component by `scalar`. If `index` is left at `-1`, then
         * this will mulitply all components.
         * 
         * @param scalar `double`
         * @param index `int = -1`
         * @return `Vector<N>` 
         */
        Vector<N> times(double scalar, int index = -1);

        /**
         * @brief Divide a given component by `scalar`. If `index` is left at `-1`, then
         * this will divide all components.
         * 
         * @param scalar `double`
         * @param index `int = -1`
         * @return `Vector<N>` 
         */
        Vector<N> divided_by(double scalar, int index = -1);

        /**
         * @brief Get the dot product of this vector with another vector
         * 
         * @param other `const Vector<N>&`
         * @return `double` 
         */
        double dot(const Vector<N>& other);

        /**
         * @brief Add this vector with another
         * 
         * @param other `const Vector<N>&` 
         * @return Vector<N> 
         */
        Vector<N> plus(const Vector<N>& other);

        /**
         * @brief Subtract this vector with another
         * 
         * If this vector is `VecA` and `other` is `VecB`
         * 
         * Then this is just `VecA - VecB`
         * 
         * @param other `const Vector<N>&`
         * @return `Vector<N>` 
         */
        Vector<N> minus(const Vector<N>& other);

        /**
         * @brief Gets if this vector is equal to another, if they are the same dimension
         * and they have the same values at each index
         * 
         * @param other `const Vector<N>&`
         * @return `true` If size and all values are same 
         * @return `false` Otherwise 
         */
        bool equals(const Vector<N>& other);

        /**
         * @brief Gets a reference to the value at the given index. This is functionally the same as `at()`
         * 
         * @param index `int`
         * @return `double&` 
         */
        double& operator[](size_t index);

        /**
         * @brief Gets the const reference to the value at the given index. This is functionally the same as `get()`
         * 
         * @param index `int`
         * @return `const double&` 
         */
        const double& operator[](size_t index) const;

        // TODO: Implement these
        // Vector<N> operator+(const Vector<N>& other) const;
        // Vector<N> operator-(const Vector<N>& other) const;
        // Vector<N> operator/(const Vector<N>& other) const;

        // Vector<N>& operator=(const Vector<N>& other);
        // Vector<N>& operator+=(const Vector<N>& other);
        // Vector<N>& operator-=(const Vector<N>& other);

        // bool operator==(const Vector<N>& other) const;

        /**
         * @brief Convert the vector to a formatted string.
         * 
         * If `use_multi_line = true` then the output will be something like
         * 
         * ```
         * ( 0 ) 15.00
         * ( 1 ) 123.312
         * ( 3 ) 13232.3123
         * ```
         * 
         * If `use_multi_line = false` then the output will be something like
         * 
         * ```
         * 15.000, 123.312, 131232.1328
         * ```
         * 
         * @param use_multi_line `bool = true` Set to true to print out each component in separate lines.
         * Set to false to print out all components on the same line
         * @return `std::string` 
         */
        std::string to_string(bool use_multi_line = true);

    private:

        // The dimension (fixed at initialization)
        int m_size;

        // Vector based element storage
        std::vector<double> m_data;        


}; // class Vector


#include "plib/math/n_vector.tpp"


#endif // N_VECTOR_HPP