#ifndef PBN_PARSER_H
#define PBN_PARSER_H

#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include "reader.h"
#include "types.h"

namespace nobridge::pbn {

    struct Tag {
        std::string name;
        std::string value;
        StringList lines;
    };

    using TagPtr = std::shared_ptr<Tag>;
    using TagMap = std::unordered_map<std::string, TagPtr>;
    using GameList = std::vector<TagMap>;

    class Parser {
       public:
        explicit Parser(Reader& reader) : m_reader(reader) {}
        [[nodiscard]] GameList run() const;

       private:
        Reader& m_reader;
    };

}  // namespace nobridge::pbn

// Overload << for std::ostream
inline std::ostream& operator<<(std::ostream& os, const nobridge::pbn::Tag& t) {
    os << "Tag(name: " << t.name << ", value: " << t.value << ")";
    return os;
}

#endif
