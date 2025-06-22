

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

        std::string sdeal = pbn::getTagValue(tags, "Deal");
        std::string sdealer = pbn::getTagValue(tags, "Dealer");
        std::string svuln = pbn::getTagValue(tags, "Vulnerable");
        /////////////////////////////////
        // Player
        engine::DealList deal = toDeal(sdeal);
        StringArray<4> directions{"North", "East", "South", "West"};
        if (deal.size() == 4) {
            for (std::size_t i = 0; i < directions.size(); ++i) {
                std::string dir = directions[i];
                std::string d = dir.substr(0, 1);
                if (const pbn::TagPtr& tag = pbn::getTag(tags, dir)) {
                    engine::HandPtr hand = std::make_shared<engine::Hand>(
                        deal[i], d == sdealer, svuln.contains(d));

                    engine::PlayerPtr player = std::make_shared<engine::Player>(
                        engine::PlayerType::HUMAN,
                        static_cast<engine::Direction>(i), hand);
                    game->addPlayer(player);
                }
            }
        }
        return game;
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
        std::array<engine::Suit, 4> suit_enums{
            engine::Suit::SPADES, engine::Suit::HEARTS, engine::Suit::DIAMONDS,
            engine::Suit::CLUBS};
        LegendMapT<char, engine::Rank> rank_enums{
            {'2', engine::Rank::TWO},   {'3', engine::Rank::THREE},
            {'4', engine::Rank::FOUR},  {'5', engine::Rank::FIVE},
            {'6', engine::Rank::SIX},   {'7', engine::Rank::SEVEN},
            {'8', engine::Rank::EIGHT}, {'9', engine::Rank::NINE},
            {'T', engine::Rank::TEN},   {'J', engine::Rank::JACK},
            {'Q', engine::Rank::QUEEN}, {'K', engine::Rank::KING},
            {'A', engine::Rank::ACE},
        };
        engine::DealList deals;

        StringList hands = mika::string::split(
            dealstr.contains(':') ? dealstr.substr(2) : "", ' ');
        for (auto hand : hands) {
            engine::CardList deal;
            if (hand != "-") {
                StringList suits = mika::string::split(hand, '.');
                for (auto it = suits.begin(); it != suits.end(); ++it) {
                    std::size_t index = it - suits.begin();
                    for (char c : (*it)) {
                        deal.push_back(std::make_shared<engine::Card>(
                            suit_enums[index], rank_enums[c]));
                    }
                }
            }
            deals.push_back(deal);
        }
        return deals;
    }  // namespace pbn
}  // namespace nobridge::adapter
