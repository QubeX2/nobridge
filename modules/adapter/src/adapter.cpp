

#include "adapter.h"

#include <map>
#include <memory>
#include <print>
#include <vector>

#include "card.h"
#include "deck.h"
#include "engine.h"
#include "mika.h"
#include "vect.h"

namespace nobridge::adapter {
    namespace pbn {
        engine::DealList toDeal(const std::string &dealstr) {
            std::array<engine::Suit, 4> suit_enums{
                engine::Suit::SPADES, engine::Suit::HEARTS,
                engine::Suit::DIAMONDS, engine::Suit::CLUBS};
            std::map<char, engine::Rank> rank_enums{
                {'2', engine::Rank::TWO},   {'3', engine::Rank::THREE},
                {'4', engine::Rank::FOUR},  {'5', engine::Rank::FIVE},
                {'6', engine::Rank::SIX},   {'7', engine::Rank::SEVEN},
                {'8', engine::Rank::EIGHT}, {'9', engine::Rank::NINE},
                {'T', engine::Rank::TEN},   {'J', engine::Rank::JACK},
                {'Q', engine::Rank::QUEEN}, {'K', engine::Rank::KING},
                {'A', engine::Rank::ACE},
            };
            engine::DealList deals;

            std::vector<std::string> hands = mika::string::split(
                dealstr.contains(':') ? dealstr.substr(2) : "", ' ');
            for (auto hand : hands) {
                engine::CardList deal;
                if (hand != "-") {
                    std::vector<std::string> suits =
                        mika::string::split(hand, '.');
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
        }
    }  // namespace pbn
}  // namespace nobridge::adapter
