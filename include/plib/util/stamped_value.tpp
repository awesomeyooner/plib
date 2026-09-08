#include "plib/util/stamped_value.hpp"


template <typename T>
StampedValue<T>::StampedValue(T value, double timestamp)
{
    update(value, timestamp);

} // end of "StampedValue(T, double)"


template <typename T>
StampedValue<T>::StampedValue(T value)
{
    update(value);

} // end of "StampedValue(T)"


template<typename T>
void StampedValue<T>::update(T value, double timestamp)
{
    // Save the previous values before updating
    m_prev_value = m_value;
    m_prev_timestamp = timestamp;

    // Update new values
    m_value = value;
    m_timestamp = timestamp;

} // end of "update(T, double)"


template<typename T>
void StampedValue<T>::update(T value)
{
    double time = System::get_epoch();

    update(value, time);

} // end of "update(T, double)"


template<typename T>
T StampedValue<T>::get_value()
{
    return m_value;

} // end of "get_value()"


template<typename T>
double StampedValue<T>::get_timestamp()
{
    return m_timestamp;

} // end of "get_timestamp()"


template<typename T>
double StampedValue<T>::get_rate()
{
    double dv = get_dv();
    double dt = get_dt();

    // Avoid division by 0
    if(dt == 0)
        return 0;

    return dv / dt;

} // end of "get_rate()"


template<typename T>
T StampedValue<T>::get_dv()
{
    return m_value - m_prev_value;

} // end of "get_dv()"


template<typename T>
double StampedValue<T>::get_dt()
{
    return m_timestamp - m_prev_timestamp;

} // end of "get_dt()"