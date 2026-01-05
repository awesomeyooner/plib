#include "plib/math/motion/cubic_hermite_spline.hpp"


CubicHermiteSpline::CubicHermiteSpline()
{
    // Leave this here for now to make testing with desmos easier
    m_P0 = 0;
    m_v0 = 0;
    m_P1 = 20;
    m_v1 = 0;

    m_j_max = 10;
    m_a_max = 10;
    m_v_max = 10;

} // end of "CubicHermiteSpline"


double CubicHermiteSpline::get_kj()
{
    // Define shorthands
    double a = ( 2 * m_P0 ) - ( 2 * m_P1 );
    double b = m_v0 + m_v1;
    double c = 0;
    double d = - m_j_max / 6;

    // Convert into a depressed cubic
    // TODO: verify that you can just remove all terms multiplied by c
    double p = ( ( 3 * a * c) - ( b * b ) ) / ( 3 * a * a );
    double q = ( ( 2 * std::pow(b, 3) ) - ( 9 * a * b * c ) + ( 27 * a * a * d ) ) / ( 27 * std::pow(a, 3) );
    
    // Use Cardrano's Formula to solve for the real root
    // https://en.wikipedia.org/wiki/Cubic_equation
    double discriminant = ( q * q / 4 ) + ( p * p * p / 27 );
    double sqrt_discriminant = std::pow(discriminant, 1.0 / 2.0);

    double u1 = ( -q / 2) + sqrt_discriminant;
    double u2 = ( -q / 2) - sqrt_discriminant;

    // For some reason std::pow( ... , 1.0 / 3.0) doesn't like negative numbers, so I'm doing this
    // as a temporary workaround until I can find a cleaner way
    double cube_root_u1 = std::copysign(std::pow( std::abs(u1) , 1.0 / 3.0), u1);
    double cube_root_u2 = std::copysign(std::pow( std::abs(u2) , 1.0 / 3.0), u2);

    // You can use roots of unity (cubic) to find the other two
    double root = cube_root_u1 + cube_root_u2;

    // k must be positive
    return std::abs(root);

} // end of "get_kj"


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
    double kj = get_kj();
    double ka = get_ka();
    double kv = get_kv();

    // Return the smaller of the three but excluding 0
    return nonzero_min(kj, ka, kv);

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


// This is just a helper function to clean up my methods
double CubicHermiteSpline::nonzero_min(double a, double b)
{
    // If one is 0, return the other
    if( a == 0 && b != 0)
        return b;
    else if( b == 0 && a != 0)
        return a;
    
    // Is b smaller than a? Then return b. Else return a;'
    return a > b ? b : a;

} // end of "nonzero_min"


// This is just a helper function to clean up my methods
double CubicHermiteSpline::nonzero_min(double a, double b, double c)
{
    // If only 1 is nonzero, then return that one
    if(a == 0 && b == 0 && c != 0)
        return c;
    if( a == 0 && c== 0 && b != 0)
        return b;
    else if( b == 0 && c == 0 && a != 0)
        return a;

    double min_of_ab = nonzero_min(a, b);
    
    // Is the min of a and b smaller than c? Then return that. Else return c 
    return min_of_ab < c ? min_of_ab : c;
    
} // end of "nonzero_min"