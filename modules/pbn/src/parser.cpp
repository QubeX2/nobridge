
#include "parser.h"

#include <algorithm>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "mika.h"
#include "pbn.h"

namespace nobridge::pbn {
    const TagPtr getTag(TagMap map, std::string name) {
        return map.contains(name) ? map[name] : nullptr;
    }
    std::string getTagValue(TagMap map, std::string name) {
        const TagPtr tp = getTag(map, name);
        if (tp != nullptr) {
            return tp->value;
        }
        return "";
    }
    StringList getTagLines(TagMap map, std::string name) {
        const TagPtr tp = getTag(map, name);
        if (tp != nullptr) {
            return tp->lines;
        }
        return StringList{};
    }

    GameList Parser::run() const {
        if (m_reader.ok()) {
            GameList games;
            TagMap tmap;
            std::string cur_tag_name;
            // parse into a map-tags first
            while (!m_reader.eof()) {
                // handle a tag
                std::string line = m_reader.nextLine();
                mika::string::trim(line, " \t\r\n");
                if (line.starts_with('[')) {
                    // handle tag
                    std::smatch matches;
                    if (std::regex_search(
                            line, matches,
                            std::regex(R"(\[(.*)[ ]{1}\"(.*)\"\])"))) {
                        if (matches.size() >= 3) {
                            cur_tag_name = matches[1];
                            const auto tp = std::make_shared<Tag>(
                                Tag{.name = matches[1], .value = matches[2]});
                            tmap[matches[1]] = tp;
                        }
                    }

                } else if (line.empty()) {
                    // check if a new game
                    if (!tmap.empty()) {
                        games.push_back(tmap);
                        tmap.clear();
                    }
                } else if (!cur_tag_name.empty()) {
                    // items under a tag
                    if (tmap.contains(cur_tag_name)) {
                        const auto tp = tmap[cur_tag_name];
                        tp->lines.push_back(line);
                    }
                }
            }
            return games;
        }
        return GameList{};
    }

}  // namespace nobridge::pbn
