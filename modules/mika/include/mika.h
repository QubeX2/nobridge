#ifndef MIKA_H
#define MIKA_H

#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * string helpers
 */
namespace mika {
    namespace string {
        void trim(std::string& str, const std::string chars);
        std::vector<std::string> split(const std::string& input,
                                       char delimiter);
        bool is_anyof(const char& ch, const std::string& chars);
        std::string tolower(std::string& str);
        std::string ucfirst(std::string& str);
    }  // namespace string

    namespace map {
        template <typename K, typename V>
        void print(const std::unordered_map<K, V>& m) {
            for (const auto& [key, value] : m) {
                std::cout << key << ": " << value << '\n';
            }
        }
    }  // namespace map

    namespace array {
        template <typename T, std::size_t N>
        void join(std::ostream& os, const std::array<T, N>& arr,
                  const std::string& separator = ", ") {
            os << std::fixed << std::setprecision(2);
            for (std::size_t i = 0; i < N; ++i) {
                if (i != 0) os << separator;
                os << arr[i];
            }
        }

    }  // namespace array
}  // namespace mika

#endif
