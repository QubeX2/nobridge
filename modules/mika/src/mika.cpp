#include "mika.h"

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>

namespace mika::string {

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
    std::vector<std::string> split(const std::string& input, char delimiter) {
        std::stringstream ss(input);
        std::string item;
        std::vector<std::string> result;

        while (std::getline(ss, item, delimiter)) {
            result.push_back(item);
        }

        return result;
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
        std::string nstr = mika::string::tolower(str);
        if (!nstr.empty()) {
            nstr[0] = std::toupper(str[0]);
        }
        return nstr;
    }

}  // namespace mika::string

namespace mika::array {}
