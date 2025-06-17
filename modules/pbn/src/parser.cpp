
#include "parser.h"

#include <algorithm>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "mkrl.h"
#include "pbn.h"

namespace nobridge::pbn {
    TagList::iterator find_tag(TagList::iterator begin, TagList::iterator end,
                               std::string name) {
        for (auto it = begin; it != end; ++it) {
            if (mkrl::string::tolower(name) ==
                mkrl::string::tolower((*it)->name)) {
                return it;
            }
        }
        return end;
    }

    GameList Parser::run() {
        GameList games;
        std::map<std::string, TagPtr> tags;
        std::string cur_tag_name;
        TagList list;

        if (m_reader.ok()) {
            // parse into a map-tags first
            while (!m_reader.eof()) {
                // handle a tag
                std::string line = m_reader.nextLine();
                mkrl::string::trim(line, " \t\r\n");
                if (line.starts_with('[')) {
                    // handle tag
                    std::smatch matches;
                    if (std::regex_search(
                            line, matches,
                            std::regex(R"(\[(.*)[ ]{1}\"(.*)\"\])"))) {
                        if (matches.size() >= 3) {
                            cur_tag_name = matches[1];
                            TagPtr tp = std::make_shared<Tag>(
                                Tag{.name = matches[1], .value = matches[2]});
                            list.push_back(tp);
                            tags[matches[1]] = tp;
                        }
                    }

                } else if (line.length() == 0) {
                    // check if a new game
                    tags.clear();
                    if (list.size()) {
                        games.push_back(list);
                    }
                    list.clear();

                } else if (cur_tag_name.size()) {
                    // items under a tag
                    if (tags.contains(cur_tag_name)) {
                        TagPtr tp = tags[cur_tag_name];
                        tp->lines.push_back(line);
                    }
                }
            }
        }
        return games;
    }

}  // namespace nobridge::pbn
