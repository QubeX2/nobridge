#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace nobridge {

    template <typename K>
    using LegendMap = std::unordered_map<K, std::string>;
    template <typename K, typename V>
    using LegendMapT = std::unordered_map<K, V>;

    template <std::size_t N>
    using UIntArray = std::array<uint8_t, N>;

    using StringList = std::vector<std::string>;
    using ByteData = std::pair<const char*, std::size_t>;

    template <std::size_t N>
    using FloatArray = std::array<float, N>;

    template <std::size_t N>
    using StringArray = std::array<std::string, N>;

    namespace ansi {
        // --- Style Codes ---
        const std::string RESET = "\033[0m";
        const std::string BOLD = "\033[1m";
        const std::string DIM = "\033[2m";
        const std::string ITALIC = "\033[3m";
        const std::string UNDERLINE = "\033[4m";
        const std::string BLINK = "\033[5m";
        const std::string REVERSE = "\033[7m";
        const std::string HIDDEN = "\033[8m";

        // --- Foreground Color Codes ---
        namespace fg {
            const std::string BLACK = "\033[30m";
            const std::string RED = "\033[31m";
            const std::string GREEN = "\033[32m";
            const std::string YELLOW = "\033[33m";
            const std::string BLUE = "\033[34m";
            const std::string MAGENTA = "\033[35m";
            const std::string CYAN = "\033[36m";
            const std::string WHITE = "\033[37m";
            const std::string BRIGHT_BLACK = "\033[90m";
            const std::string BRIGHT_RED = "\033[91m";
            const std::string BRIGHT_GREEN = "\033[92m";
            const std::string BRIGHT_YELLOW = "\033[93m";
            const std::string BRIGHT_BLUE = "\033[94m";
            const std::string BRIGHT_MAGENTA = "\033[95m";
            const std::string BRIGHT_CYAN = "\033[96m";
            const std::string BRIGHT_WHITE = "\033[97m";
        }  // namespace fg

        // --- Background Color Codes ---
        namespace bg {
            const std::string BLACK = "\033[40m";
            const std::string RED = "\033[41m";
            const std::string GREEN = "\033[42m";
            const std::string YELLOW = "\033[43m";
            const std::string BLUE = "\033[44m";
            const std::string MAGENTA = "\033[45m";
            const std::string CYAN = "\033[46m";
            const std::string WHITE = "\033[47m";
            const std::string BRIGHT_BLACK = "\033[100m";
            const std::string BRIGHT_RED = "\033[101m";
            const std::string BRIGHT_GREEN = "\033[102m";
            const std::string BRIGHT_YELLOW = "\033[103m";
            const std::string BRIGHT_BLUE = "\033[104m";
            const std::string BRIGHT_MAGENTA = "\03-3[105m";
            const std::string BRIGHT_CYAN = "\033[106m";
            const std::string BRIGHT_WHITE = "\033[107m";
        }  // namespace bg

    }  // namespace ansi

}  // namespace nobridge

#endif
