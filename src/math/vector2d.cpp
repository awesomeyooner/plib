#include "plib/math/vector2d.hpp"


using namespace std;


Vector2d::Vector2d(double default_values)
    : Vector(default_values){}


Vector2d::Vector2d(initializer_list<double> list)
    : Vector(list){}


Vector2d::Vector2d(double x, double y)
    :Vector2d({x, y}){}


Vector2d Vector2d::rotate(double radians)
{
    double x = get(0);
    double y = get(1);

    double cos = std::cos(radians);
    double sin = std::sin(radians);

    // Standard 2D rotation matrix
    // V' = Rot Matrix * V
    // [ cos  -sin ]
    // [ sin  cos  ]
    double x_p = x * cos - y * sin;
    double y_p = x * sin + y * cos;

    return {x_p, y_p};

} // end of "rotate(double)"