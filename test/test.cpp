#include <iostream>

#include "plib/util/util.hpp"


int main()
{
    util::print("Hello World!");

    status_utils::StatusedValue<std::string> input = util::get_user_input_string("Enter a string: ");

    util::print(input.to_string());
    util::print({"You said: ", input.value});

    return 0;
}