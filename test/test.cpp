#include <iostream>
#include <cstdio>
#include <type_traits>

#include "plib/util/util.hpp"
#include "plib/util/system.hpp"

#include "plib/math/motion/cubic_hermite_spline.hpp"

#include "plib/math/control/pid_controller.hpp"

#include "plib/math/n_vector.hpp"


using namespace std;


void test_vector()
{
    Vector<3> vec3 = {-100, 0, 100};

    double average = vec3.get_min();

    cout << average << endl;
}


int main()
{
    test_vector();

    return 0;

} // end of "main"