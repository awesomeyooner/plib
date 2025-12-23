#ifndef POINT2D_HPP
#define POINT2D_HPP

#include <cmath>

#include "math_helper.hpp"
#include "vector2d.hpp"

class Point2D{

    public:

        Point2D(double _x = 0, double _y = 0){
            x = _x;
            y = _y;
        }

        static Point2D from_native(double _x, double _y){
            return Point2D(
                conversions::native_to_cartesian_X(_x), 
                conversions::native_to_cartesian_Y(_y)
            );
        }

        Point2D get_point2d(){
            return *this;
        }

        Vector2D get_vector2d(){
            return Vector2D(x, y);
        }

        Vector2D to_vector2d(Point2D other){
            return minus(other).get_vector2d();
        }

        Point2D copy(){
            return Point2D(x, y);
        }

        Point2D set_point(Point2D other){
            set(other.x, other.y);
            return *this;
        }

        Point2D set(double _x, double _y){
            x = _x;
            y = _y;
            return *this;
        }

        Point2D set_X(double _x){
            x = _x;
            return *this;
        }

        Point2D set_Y(double _y){
            y = _y;
            return *this;
        }

        Point2D with_X(double _x){
            return Point2D(_x, y);
        }

        Point2D with_Y(double _y){
            return Point2D(x, _y);
        }

        double get_native_X(){
            return conversions::cartesian_to_native_X(x);
        }

        double get_native_Y(){
            return conversions::cartesian_to_native_Y(y);
        }

        double get_X(){
            return x;
        }

        double get_Y(){
            return y;
        }

        double get_distance(Point2D other){
            double dX = x - other.x;
            double dY = y - other.y;
            
            return sqrt((dX * dX) + (dY * dY));
        }

        Point2D plus(Point2D other){
            double sum_X = x + other.x;
            double sum_Y = y + other.y;

            return Point2D(sum_X, sum_Y);
        }

        Point2D minus(Point2D other){
            double dX = x - other.x;
            double dY = y - other.y;

            return Point2D(dX, dY);
        }

        bool is_out_of_bounds(double w = conversions::width, double h = conversions::height){
            if(x > w / 2 || x < -w / 2)
                return true;

            if(y > h / 2 || y < -h / 2)
                return true;

            return false;
        }

    private:

        double x;
        double y;

}; // class Point2D

#endif // POINT2D_HPP 