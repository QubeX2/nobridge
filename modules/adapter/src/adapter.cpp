

#include "adapter.h"

#include <memory>

#include "card.h"
#include "deck.h"
#include "game.h"
#include "mika.h"
#include "parser.h"
#include "player.h"
#include "types.h"

namespace nobridge::adapter {

    /**
     *
     */
    engine::GamePtr toGame(nobridge::pbn::TagMap tags) {
        engine::GamePtr game = std::make_shared<engine::Game>();
        /////////////////////////////////
        // Player
        std::string sdeal = pbn::getTagValue(tags, "Deal");
        std::string sdealer = pbn::getTagValue(tags, "Dealer");
        std::string svuln = pbn::getTagValue(tags, "Vulnerable");
        engine::DealList deal = toDeal(sdeal);
        StringArray<4> directions{"North", "East", "South", "West"};
        if (deal.size() == 4) {
            for (std::size_t i = 0; i < directions.size(); ++i) {
                std::string dir = directions[i];
                std::string d = dir.substr(0, 1);
                if (const pbn::TagPtr& tag = pbn::getTag(tags, dir)) {
                    // Vulnerable
                    bool vuln = false;
                    if (svuln == "All" || svuln == "Both") {
                        vuln = true;
                    } else if ((d == "N" or d == "S") && svuln == "NS") {
                        vuln = true;
                    } else if ((d == "E" or d == "W" && svuln == "EW")) {
                        vuln = true;
                    }

                    engine::HandPtr hand = std::make_shared<engine::Hand>(
                        deal[i], d == sdealer, vuln);

                    std::string name = pbn::getTagValue(tags, dir);
                    engine::PlayerPtr player = std::make_shared<engine::Player>(
                        name, engine::PlayerType::HUMAN,
                        static_cast<engine::Direction>(i + 1), hand);
                    game->addPlayer(player);
                }
            }
        }
        /////////////////////////////////
        // Play
        pbn::TagPtr tag = pbn::getTag(tags, "Play");
        for (auto line : tag->lines) {
            StringList cards = mika::string::split(line, ' ');
            for (auto card : cards) {
            }
        }

        /////////////////////////////////
        // Auction

        return game;
    }

    /**
     *
     */
    engine::CardPtr toCard(const std::string& string) {
        if (string.length() == 2) {
            std::string suit = string.substr(0, 1);
            std::string rank = string.substr(1, 1);
            if (std::string("SHDC").contains(suit)) {
                engine::CardPtr card = std::make_shared<engine::Card>(
                    engine::SUIT_MAP.at(suit[0]), engine::RANK_MAP.at(rank[0]));
                return card;
            }
        }
        return nullptr;
    }

    /**
     *
     */
    std::string toHandstr(const engine::CardList cards) {
        StringArray<4> suits;
        for (auto card : cards) {
            suits[static_cast<std::size_t>(card->suit()) - 1] +=
                card->rankText();
        }
        return mika::array::join(suits, ".");
    }

    /**
     *
     */
    engine::DealList toDeal(const std::string& dealstr) {
        engine::DealList deals;

        StringList hands = mika::string::split(
            dealstr.contains(':') ? dealstr.substr(2) : "", ' ');
        for (auto hand : hands) {
            engine::CardList deal;
            if (hand != "-") {
                StringList suits = mika::string::split(hand, '.');
                for (auto it = suits.begin(); it != suits.end(); ++it) {
                    std::size_t index2 = it - suits.begin();
                    for (char c : (*it)) {
                        deal.push_back(std::make_shared<engine::Card>(
                            engine::SUIT_ARRAY[index2],
                            engine::RANK_MAP.at(c)));
                    }
                }
            }
            deals.push_back(deal);
        }
        return deals;
    }  // namespace pbn
}  // namespace nobridge::adapter
