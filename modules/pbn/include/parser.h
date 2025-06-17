#ifndef PBN_PARSER_H
#define PBN_PARSER_H

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
    using TagList = std::vector<TagPtr>;
    using GameList = std::vector<TagList>;

    class Parser {
       public:
        Parser(Reader& reader) : m_reader(reader) {}
        GameList run();

       private:
        Reader& m_reader;
    };

    TagList::iterator find_tag(TagList::iterator begin, TagList::iterator end,
                               std::string name);
}  // namespace nobridge::pbn

// Overload << for std::ostream
inline std::ostream& operator<<(std::ostream& os, const nobridge::pbn::Tag& t) {
    os << "Tag(name: " << t.name << ", value: " << t.value << ")";
    return os;
}

#endif
