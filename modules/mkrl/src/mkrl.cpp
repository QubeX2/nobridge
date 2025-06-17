#include "mkrl.h"

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>

namespace mkrl::string {

    /**
     *
     */
    void trim(std::string& str, std::string chars) {
        str.erase(0, str.find_first_not_of(chars));
        str.erase(str.find_last_not_of(chars) + 1);
    }

    /**
     *
     */
    bool is_anyof(const char& ch, const std::string& chars) {
        return std::any_of(std::cbegin(chars), std::cend(chars),
                           [&](const char& c) { return c == ch; });
    }

    /*
     *
     */
    std::string tolower(std::string& str) {
        std::string nstr;
        std::transform(std::begin(str), std::end(str), std::back_inserter(nstr),
                       [](unsigned char c) { return std::tolower(c); });
        return nstr;
    }

    /**
     *
     */
    std::string ucfirst(std::string& str) {
        std::string nstr = mkrl::string::tolower(str);
        if (nstr.size()) {
            nstr[0] = std::toupper(str[0]);
        }
        return nstr;
    }

}  // namespace mkrl::string

namespace mkrl::array {}
