#ifndef STRING_UTIL_HPP
#define STRING_UTIL_HPP


#include "plib/util/system.hpp"

#include <string>


namespace string_util
{

    std::string add_header(const std::string& header, const std::string& text);

    std::string timestamped_header(const std::string& header, const std::string& text);

} // namespace string_utils


#endif // STRING_UTILS_HPP