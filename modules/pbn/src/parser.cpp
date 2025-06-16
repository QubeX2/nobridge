
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

    std::unique_ptr<Pbn> Parser::run() {
        std::vector<TagList> games;
        std::map<std::string, Tag> tags;
        std::unique_ptr<Pbn> pbn = std::make_unique<Pbn>();
        std::string cur_tag_name;
        TagList list;

        if (m_reader.ok()) {
            // parse into a map-tags first
            while (!m_reader.eof()) {
                // handle a tag
                std::string line = m_reader.nextLine();
                if (line.starts_with('[')) {
                    std::smatch matches;
                    if (std::regex_search(
                            line, matches,
                            std::regex(R"(\[(.*)[ ]{1}\"(.*)\"\])"))) {
                        if (matches.size() >= 3) {
                            cur_tag_name = matches[1];
                            // check if a new game
                            if (cur_tag_name == "Event") {
                                tags.clear();
                                if (list.tags.size()) {
                                    games.push_back(list);
                                }
                                list.tags.clear();
                            }
                            Tag t{.name = matches[1], .value = matches[2]};
                            list.tags.push_back(t);
                            tags[matches[1]] = t;
                        }
                    }
                } else if (cur_tag_name.size()) {
                    if (tags.contains(cur_tag_name)) {
                        Tag t = tags[cur_tag_name];
                        t.lines.push_back(line);
                    }
                }
            }

            // write game from map-tags
            std::println("Games: {}", games.size());
            for (auto game : games) {
                std::println("  List: {}", game.tags.size());
            }
            // mkrl::map::print<std::string, Tag>(tags);
        }
        return nullptr;
    }

}  // namespace nobridge::pbn
