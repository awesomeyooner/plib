#include <iostream>

#include "plib/util/util.hpp"
#include "plib/i2c/i2c.hpp"
#include "plib/i2c/wire_device.hpp"

int main()
{
    util::print("Hello World!");

    auto input = util::get_user_input_double("Enter a number: ", true, "Sorry, your input was not a number. Please enter a number: ");

    util::print(input.value);

    return 0;
}