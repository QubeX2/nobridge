
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
    const Tag* getTag(const TagM& map, const std::string& name) {
        auto it = map.find(name);
        if (it != map.end()) {
            return it->second.get();
        }
        return nullptr;
    }

    std::string getTagValue(const TagM& map, const std::string& name) {
        const Tag* tp = getTag(map, name);
        if (tp != nullptr) {
            return tp->value;
        }
        return "";
    }

    StringL getTagLines(TagM map, std::string name) {
        const Tag* tp = getTag(map, name);
        if (tp != nullptr) {
            return tp->lines;
        }
        return StringL{};
    }

    GameL Parser::run() const {
        if (m_reader.ok()) {
            GameL games;
            TagM tmap;
            std::string cur_tag_name;
            // parse into a map-tags first
            while (!m_reader.eof()) {
                // handle a tag
                std::string line = m_reader.nextLine();
                mika::string::trim(line, " \t\r\n");
                if (line.starts_with('[')) {
                    // handle tag
                    std::smatch matches;
                    if (std::regex_search(line, matches, std::regex(R"(\[(.*)[ ]{1}\"(.*)\"\])"))) {
                        if (matches.size() >= 3) {
                            cur_tag_name = matches[1];
                            tmap.emplace(matches[1], std::make_unique<Tag>(Tag{
                                                         .name = matches[1], .value = matches[2]}));
                        }
                    }

                } else if (line.empty()) {
                    // check if a new game
                    if (!tmap.empty()) {
                        games.push_back(std::move(tmap));
                        tmap.clear();
                    }
                } else if (!cur_tag_name.empty()) {
                    // items under a tag
                    if (tmap.contains(cur_tag_name)) {
                        Tag* tp = tmap.at(cur_tag_name).get();
                        tp->lines.push_back(line);
                    }
                }
            }
            return games;
        }
        return GameL{};
    }

}  // namespace nobridge::pbn
