#include "plib/util/string_util.hpp"


using namespace std;


string string_util::add_header(const string& header, const string& text)
{
    // [ HEADER ]: Hellow World!
    return "[ " + header + " ]: " + text;

} // end of "add_header(const std::string&, const std::string&)"


string string_util::timestamped_header(const string& header, const string& text)
{
    double time = System::get_epoch();
    string formatted = "[ " + to_string(time) + " ] " + add_header(header, text);

    // [ 0.0032331127 ] [ HEADER ]: Hello World!
    return formatted;

} // end of "timestamped_header(const std::string&, const std::string&))"