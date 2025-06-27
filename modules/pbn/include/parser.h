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
        StringL lines;
    };

    using TagP = std::shared_ptr<Tag>;
    using TagM = std::unordered_map<std::string, TagP>;
    using GameL = std::vector<TagM>;

    class Parser {
       public:
        explicit Parser(Reader& reader) : m_reader(reader) {}
        [[nodiscard]] GameL run() const;

       private:
        Reader& m_reader;
    };

    const TagP getTag(TagM map, std::string name);
    std::string getTagValue(TagM map, std::string name);
    StringL getTagLines(TagM map, std::string name);

}  // namespace nobridge::pbn

// Overload << for std::ostream
inline std::ostream& operator<<(std::ostream& os, const nobridge::pbn::Tag& t) {
    os << "Tag(name: " << t.name << ", value: " << t.value << ")";
    return os;
}

#endif
