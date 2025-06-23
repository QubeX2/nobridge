#ifndef MIKA_H
#define MIKA_H

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "types.h"

/**
 * string helpers
 */
namespace mika {
    namespace math {
        float toDegree(float radian);
    }  // namespace math

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
        template <std::size_t N>
        void str2arr(std::array<char, N>& arr, const std::string& s) {
            arr.fill('\0');
            std::size_t clen = std::min(s.length(), N);
            std::copy_n(s.begin(), clen, arr.begin());
        }

        template <typename T, std::size_t N>
        std::string join(
            const std::array<T, N>& arr, const std::string& separator = ", ",
            std::unordered_map<std::size_t, std::string> legend = {}) {
            std::stringstream os;
            os << std::fixed << std::setprecision(2);
            for (std::size_t i = 0; i < N; ++i) {
                if (i != 0) os << separator;
                if (!legend.empty()) {
                    os << nobridge::ansi::fg::BLUE << legend[i] << ": "
                       << nobridge::ansi::RESET << arr[i];

                } else {
                    os << arr[i];
                }
            }
            return os.str();
        }

        template <typename T, std::size_t N>
        void join(std::ostream& os, const std::array<T, N>& arr,
                  const std::string& separator = ", ",
                  std::unordered_map<std::size_t, std::string> legend = {}) {
            os << std::fixed << std::setprecision(2);
            for (std::size_t i = 0; i < N; ++i) {
                if (i != 0) os << separator;
                if (!legend.empty()) {
                    os << nobridge::ansi::fg::BLUE << legend[i] << ": "
                       << nobridge::ansi::RESET << arr[i];

                } else {
                    os << arr[i];
                }
            }
        }

    }  // namespace array
}  // namespace mika

#endif
