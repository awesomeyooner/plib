#include "plib/math/motion/cubic_hermite_spline.hpp"


CubicHermiteSpline::CubicHermiteSpline()
{
    // nothing to do for now
} // end of "CubicHermiteSpline"


double CubicHermiteSpline::get_ka()
{
    double a = -3 * m_P0 + 3 * m_P1;
    double b = -2 * m_v0 - m_v1;
    double c = - m_a_max / 2;
    
    // Calculate the roots using quadratic formula

    double discriminant = (b * b) - (4 * a * c);

    if(discriminant > 0)
    {
        return abs( (-b + sqrt(discriminant)) / (2 * a));
    }
    else
    {
        return abs( (-b - sqrt(-discriminant)) / (2 * a));
    }

} // end of "get_ka"


double CubicHermiteSpline::get_kv()
{
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
        return abs( (-b + sqrt(discriminant)) / (2 * a));
    }
    else
    {
        return abs( (-b - sqrt(-discriminant)) / (2 * a));
    }

} // end of "get_kv"


double CubicHermiteSpline::get_k()
{
    double ka = get_ka();
    double kv = get_kv();

    return ka > kv ? 
}