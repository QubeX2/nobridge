#ifndef MKRL_H
#define MKRL_H

#include <iostream>
#include <map>
#include <print>
#include <string>

namespace mkrl::string {
    void trim(std::string& str, const std::string chars);
    bool is_anyof(const char& ch, const std::string& chars);
    std::string tolower(std::string& str);
    std::string ucfirst(std::string& str);

}  // namespace mkrl::string

namespace mkrl::map {
    template <typename K, typename V>
    void print(const std::map<K, V>& m) {
        for (const auto& [key, value] : m) {
            std::cout << key << ": " << value << '\n';
        }
    }
}  // namespace mkrl::map

#endif
