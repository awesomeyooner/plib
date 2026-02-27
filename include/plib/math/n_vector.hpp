#ifndef N_VECTOR_HPP
#define N_VECTOR_HPP


#include <vector>


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

        Vector(std::vector<double> values);

        Vector(const Vector<N>& other);

        double get_magnitude();

        Vector<N> get_unit_vector();

        int get_dimension();

        double get(int index);

        void set(double value, int index);

        Vector<N> times(double scalar, int index = -1);

        Vector<N> divided_by(double scalar, int index = -1);

        Vector<N> dot(const Vector<N>& other);

        Vector<N> plus(const Vector<N>& other);

        Vector<N> minus(const Vector<N>& other);

        double& operator[](size_t index);
        const double& operator[](size_t index) const;

        Vector<N> operator+(const Vector<N>& other) const;
        Vector<N> operator-(const Vector<N>& other) const;
        Vector<N> operator*(const Vector<N>& other) const;
        Vector<N> operator/(const Vector<N>& other) const;

        Vector<N>& operator=(const Vector<N>& other);
        Vector<N>& operator+=(const Vector<N>& other);
        Vector<N>& operator-=(const Vector<N>& other);
        Vector<N>& operator*=(const Vector<N>& other);
        Vector<N>& operator/=(const Vector<N>& other);

        bool operator==(const Vector<N>& other) const;

    private:

        // The dimension (fixed)
        int m_size;

        // Vector based element storage
        std::vector<double> m_data;        


}; // class Vector


#include "plib/math/n_vector.tpp"


#endif // N_VECTOR_HPP