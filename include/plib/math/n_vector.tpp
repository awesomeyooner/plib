#include "plib/math/n_vector.hpp"


template <int N>
Vector<N>::Vector(double default_value)
{
    // Set the size
    m_size = N;

    // For N values, set their value to the default
    for(size_t i = 0; i < m_size; i++)
    {
        m_data.at(i) = default_value;
    }

} // end of "Vector(double)"


template <int N>
Vector<N>::Vector(std::initializer_list<double> list) :
    m_data(list)
{
    m_size = N;

} // end of "Vector(std::initializer_list<double>)"


template <int N>
Vector<N>::Vector(std::vector<double> data)
{
    m_size = N;

    // For N values, set copy the values
    for(size_t i = 0; i < m_size; i++)
    {
        m_data.at(i) = data.at(i);
    }

} // end of "Vector(std::vector<double>)"


template <int N>
Vector<N>::Vector(const Vector<N>& data)
{
    m_size = N;

    // For N values, set copy the values
    for(size_t i = 0; i < m_size; i++)
    {
        m_data.at(i) = data.at(i);
    }

} // end of "Vector(std::vector<double>)"


template <int N>
double Vector<N>::get_magnitude()
{
    double dot_product = dot(this);

    return sqrt(dot_product);

} // end of "get_magnitude()"


template <int N>
Vector<N> Vector<N>::get_unit_vector()
{
    double magnitude = get_magnitude();

    return this->divided_by(magnitude);
}