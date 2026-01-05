#include "plib/math/motion/cubic_hermite_spline.hpp"


CubicHermiteSpline::CubicHermiteSpline()
{
    // Leave this here for now to make testing with desmos easier
    m_P0 = 0;
    m_v0 = 0;
    m_P1 = 20;
    m_v1 = 0;

    m_a_max = 10;
    m_v_max = 10;

} // end of "CubicHermiteSpline"


double CubicHermiteSpline::get_ka()
{
    // Math defined in my notes
    double a = -3 * m_P0 + 3 * m_P1;
    double b = -2 * m_v0 - m_v1;
    double c = - m_a_max / 2;
    
    // Calculate the roots using quadratic formula

    double discriminant = (b * b) - (4 * a * c);

    if(discriminant > 0)
    {
        return std::abs( (-b + std::sqrt(discriminant)) / (2 * a));
    }
    else
    {
        return std::abs( (-b - std::sqrt(-discriminant)) / (2 * a));
    }

} // end of "get_ka"


double CubicHermiteSpline::get_kv()
{
    // Math defined in my notes
    double c1 = 2 * m_P0 - 2 * m_P1;
    double c2 = m_v0 + m_v1;
    double c3 = 3 * (m_P1 - m_P0);
    double c4 = (2 * m_v0) + m_v1;

    double a = c3 * c3;
    double b = -( (2 * c3 * c4) + (3 * c1 * (m_v0 - m_v_max)) );
    double c = (c4 * c4) - ( 3 * c2 * (m_v0 - m_v_max) );

    // Calculate the roots using quadratic formula

    double discriminant = (b * b) - (4 * a * c);

    if(discriminant > 0)
    {
        return std::abs( (-b + std::sqrt(discriminant)) / (2 * a));
    }
    else
    {
        return std::abs( (-b - std::sqrt(-discriminant)) / (2 * a));
    }

} // end of "get_kv"


double CubicHermiteSpline::get_k()
{
    double ka = get_ka();
    double kv = get_kv();

    // If either one is zero, return the other
    if(ka == 0 && kv != 0)
        return kv;
    else if(kv == 0 && ka != 0)
        return ka;

    // Return the smaller of the two
    return ka > kv ? kv : ka; 

} // end of "get_k"


double CubicHermiteSpline::get_total_time()
{
    return 1 / get_k();

} // end of "get_total_time"


double CubicHermiteSpline::P(double t)
{
    double k = get_k();

    double r1m = m_P0;
    double r2m = m_v0 / k;
    double r3m = ( -3 * m_P0 ) - ( 2 * m_v0 / k ) + ( 3 * m_P1 ) - ( m_v1 / k );
    double r4m = ( 2 * m_P0 ) + ( m_v0 / k ) - ( 2 * m_P1 ) + ( m_v1 / k );
    
    return r1m + (r2m * k * t) + (r3m * std::pow(k, 2) * std::pow(t, 2)) + (r4m * std::pow(k, 3) * std::pow(t, 3));

} // end of "P"


double CubicHermiteSpline::P_prime_1(double t)
{
    double k = get_k();

    double r1m = m_P0;
    double r2m = m_v0 / k;
    double r3m = ( -3 * m_P0 ) - ( 2 * m_v0 / k ) + ( 3 * m_P1 ) - ( m_v1 / k );
    double r4m = ( 2 * m_P0 ) + ( m_v0 / k ) - ( 2 * m_P1 ) + ( m_v1 / k );
    
    return (r2m * k) + (2 * r3m * std::pow(k, 2) * t) + (3 * r4m * std::pow(k, 3) * std::pow(t, 2));

} // end of "P_prime_1"


double CubicHermiteSpline::P_prime_2(double t)
{
    double k = get_k();

    double r1m = m_P0;
    double r2m = m_v0 / k;
    double r3m = ( -3 * m_P0 ) - ( 2 * m_v0 / k ) + ( 3 * m_P1 ) - ( m_v1 / k );
    double r4m = ( 2 * m_P0 ) + ( m_v0 / k ) - ( 2 * m_P1 ) + ( m_v1 / k );
    
    return (2 * r3m * std::pow(k, 2)) + (6 * r4m * std::pow(k, 3) * t);

} // end of "P_prime_2"


double CubicHermiteSpline::P_prime_3(double t)
{
    double k = get_k();

    double r1m = m_P0;
    double r2m = m_v0 / k;
    double r3m = ( -3 * m_P0 ) - ( 2 * m_v0 / k ) + ( 3 * m_P1 ) - ( m_v1 / k );
    double r4m = ( 2 * m_P0 ) + ( m_v0 / k ) - ( 2 * m_P1 ) + ( m_v1 / k );
    
    return (6 * r4m * std::pow(k, 3));

} // end of "P_prime_3"