#ifndef MKRL_H
#define MKRL_H

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <map>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>

/**
 * string helpers
 */
namespace mkrl::string {
    void trim(std::string& str, const std::string chars);
    bool is_anyof(const char& ch, const std::string& chars);
    std::string tolower(std::string& str);
    std::string ucfirst(std::string& str);

}  // namespace mkrl::string

/**
 * map helpers
 */
namespace mkrl::map {
    template <typename K, typename V>
    void print(const std::map<K, V>& m) {
        for (const auto& [key, value] : m) {
            std::cout << key << ": " << value << '\n';
        }
    }
}  // namespace mkrl::map

/**
 * array helpers
 */
namespace mkrl::array {
    template <typename T, std::size_t N>
    std::string join(const std::array<T, N>& arr,
                     const std::string& separator = ", ") {
        std::ostringstream oss;
        for (std::size_t i = 0; i < N; ++i) {
            if (i != 0) oss << separator;
            oss << arr[i];
        }
        return oss.str();
    }

}  // namespace mkrl::array

#endif
