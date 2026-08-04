#include "plib/math/n_vector.hpp"


template <int N>
Vector<N>::Vector(double default_value)
{
    // Set the size
    m_size = N;

    m_data.resize(m_size);

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

    m_data.resize(m_size);

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

    m_data.resize(m_size);

    // For N values, set copy the values
    for(size_t i = 0; i < m_size; i++)
    {
        m_data.at(i) = data.get(i);
    }

} // end of "Vector(std::vector<double>)"

template <int N>
Vector<N> Vector<N>::copy()
{
    return *this;

} // end of "copy();"


template <int N>
double Vector<N>::get_magnitude()
{
    double dot_product = dot(*this);

    return sqrt(dot_product);

} // end of "get_magnitude()"

template<int N>
Vector<N> Vector<N>::with_magnitude(double magnitude)
{
    return get_unit_vector().times(magnitude);

} // end of "with_magnitude(double)"


template <int N>
Vector<N> Vector<N>::get_unit_vector()
{
    double magnitude = get_magnitude();

    return this->divided_by(magnitude);

} // end of "get_unit_vector()"


template <int N>
int Vector<N>::get_dimension()
{
    return m_size;

} // end of "get_dimension()"


template <int N>
double& Vector<N>::at(int index)
{
    return m_data.at(index);

} // end of "at(int)"


template <int N>
double Vector<N>::get(int index) const
{
    return m_data.at(index);

} // end of "at(int)"


template <int N>
void Vector<N>::set(double value, int index)
{
    if(index < 0 || index >= m_size)
        return;

    m_data.at(index) = value;

} // end of "set(double, int)"


template <int N>
Vector<N> Vector<N>::times(double scalar, int index)
{
    Vector<N> copy = Vector<N>(*this);

    // If the index was specified
    // Then only multiply that index
    if(index != -1)
    {
        copy.at(index) *= scalar;

        return copy;
    }
    // If the index was left at -1 (not specified)
    // Then multiply all values by `scalar`
    else
    {
        for(int i = 0; i < m_size; i++)
        {
            copy.at(i) *= scalar;
        }

        return copy;
    }

} // end of "times(double, int)"


template <int N>
Vector<N> Vector<N>::divided_by(double scalar, int index)
{
    Vector<N> copy = Vector<N>(*this);

    // If the index was specified
    // Then only divide that index
    if(index != -1)
    {
        copy.at(index) /= scalar;

        return copy;
    }
    // If the index was left at -1 (not specified)
    // Then divide all values by `scalar`
    else
    {
        for(int i = 0; i < m_size; i++)
        {
            copy.at(i) /= scalar;
        }

        return copy;
    }

} // end of "divided_by(double, int)"


template <int N>
double Vector<N>::dot(const Vector<N>& other)
{
    double accumulated = 0;

    for(int i = 0; i < m_size; i++)
    {
        accumulated += get(i) * other.get(i);
    }

    return accumulated;

} // end of "dot(const Vector<N>&)"


template <int N>
Vector<N> Vector<N>::plus(const Vector<N>& other)
{
    Vector<N> copy = Vector<N>(*this);

    for(int i = 0; i < m_size; i++)
    {
        copy.at(i) += other.get(i);
    }

    return copy;

} // end of "plus(const Vector<N>&)"


template <int N>
Vector<N> Vector<N>::minus(const Vector<N>& other)
{
    Vector<N> copy = Vector<N>(*this);

    for(int i = 0; i < m_size; i++)
    {
        copy.at(i) -= other.get(i);
    }

    return copy;

} // end of "minus(const Vector<N>&)"


template <int N>
bool Vector<N>::equals(const Vector<N>& other)
{
    // For every value, check if they are equal
    // If they aren't return FALSE
    for(int i = 0; i < m_size; i++)
    {
        double A = get(i);
        double B = other.get(i);

        if(A != B)
            return false;
    }

    // If code gets here, then all values must be equal

    return true;

} // end of "equals(const Vector<N>&)"

template <int N>
double& Vector<N>::operator[](size_t index)
{
    return at(index);

} // end of "operator[](size_t)"


template <int N>
const double& Vector<N>::operator[](size_t index) const
{
    return at(index);

} // end of "operator[](size_t)"


template <int N>
std::string Vector<N>::to_string(bool use_multi_line)
{
    std::string text = "";
    
    for(int i = 0; i < m_size; i++)
    {
        // ( 0 ) 15.000
        // ( 1 ) 10.000
        if(use_multi_line)
        {
            text += "( " + std::to_string(i) + " ) " + std::to_string(get(i));

            // Don't add newline to the last line
            if(i != m_size - 1)
            {
                text += "\n";
            }
        }
        // [ 15.000, 10.000, ... ]
        else
        {
            text += std::to_string(get(i));

            // Don't add space to the last line
            if(i != m_size - 1)
            {
                text += ", ";
            }
        }
    }

    return text;

} // end of "to_string()"