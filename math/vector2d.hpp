#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>

#include "math_helper.hpp"

// Forward Declaration of Point2D
class Point2D;

class Vector2D{

    public:

        Vector2D(double _x = 0, double _y = 0){
            x = _x;
            y = _y;
        }

        Vector2D get_unit_vector(){
            double magnitude = get_magnitude();

            if(magnitude == 0)
                return Vector2D();

            return Vector2D(x / magnitude, y / magnitude); 
        }

        double get_magnitude(){
            return sqrt((x * x) + (y * y));
        }

        Vector2D get_vector2d(){
            return *this;
        }

        // Forward Declaration
        Point2D to_point2d();

        Vector2D copy(){
            return Vector2D(x, y);
        }

        Vector2D set_vector(Vector2D other){
            set(other.get_X(), other.get_Y());

            return *this;
        }

        Vector2D set(double _x, double _y){
            x = _x;
            y = _y;

            return *this;
        }

        Vector2D set_X(double _x){
            x = _x;
            return *this;
        }

        Vector2D set_Y(double _y){
            y = _y;
            return *this;
        }

        Vector2D with_X(double _x){
            return Vector2D(_x, y);
        }

        Vector2D with_Y(double _y){
            return Vector2D(x, _y);
        }

        Vector2D with_magnitude(double magnitude){
            return get_unit_vector().times(magnitude);
        }

        double get_X(){
            return x;
        }

        double get_Y(){
            return y;
        }

        Vector2D times(double scalar){
            return Vector2D(x * scalar, y * scalar);
        }

        Vector2D times_X(double scalar){
            return Vector2D(x * scalar, y);
        }

        Vector2D times_Y(double scalar){
            return Vector2D(x, y * scalar);
        }

        double dot(Vector2D other){
            return (x * other.x) + (y * other.y);
        }

        Vector2D plus(Vector2D other){
            double sum_x = x + other.x;
            double sum_y = y + other.y;

            return Vector2D(sum_x, sum_y);
        }

        Vector2D minus(Vector2D other){
            double dx = x - other.x;
            double dy = y - other.y;

            return Vector2D(dx, dy);
        }

    private:

        double x;
        double y;

}; // class Vector2D

// Forward Declaration
#include "point2d.hpp"

Point2D Vector2D::to_point2d(){
            return Point2D(x, y);
}


#endif // VECTOR2D_HPP