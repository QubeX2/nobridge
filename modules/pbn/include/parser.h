#ifndef PBN_PARSER_H
#define PBN_PARSER_H

#include <memory>

#include "pbn.h"
#include "reader.h"

namespace nobridge::pbn {

    struct Tag {
        std::string name;
        std::string value;
        std::vector<std::string> lines;
    };

    struct TagList {
        std::vector<Tag> tags;
    };

    class Parser {
       public:
        Parser(Reader& reader) : m_reader(reader) {}
        std::unique_ptr<Pbn> run();

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
