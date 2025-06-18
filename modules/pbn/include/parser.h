#ifndef PBN_PARSER_H
#define PBN_PARSER_H

#include <map>
#include <memory>
#include <vector>

#include "reader.h"

namespace nobridge::pbn {

    struct Tag {
        std::string name;
        std::string value;
        std::vector<std::string> lines;
    };

    using TagPtr = std::shared_ptr<Tag>;
    using TagMap = std::map<std::string, TagPtr>;
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
