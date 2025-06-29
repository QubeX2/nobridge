#include "hand.h"

#include "types.h"

namespace nobridge::engine {
    /**
     *
     */
    UIntV Hand::toInt(const CardPU& card) {
        return (static_cast<UIntV>(card->suit()) - 1) * HAND_LENGTH +
               static_cast<UIntV>(card->rank()) - 1;
    }

    /**
     *
     */
    CardPU Hand::toCard(const UIntV num) {
        if (num < 1 || num > 52) return nullptr;
        UIntV znum = num - 1;
        UIntV suit = (num / 13) + 1;
        UIntV rank = (num % 13) + 1;
        // std::cout << std::format("Num: {}, Suit: {}, Rank: {}", num, suit, rank);
        CardPU card = std::make_unique<Card>(static_cast<Suit>(suit), static_cast<Rank>(rank));
        return std::move(card);
    }

    /**
     * STATIC
     */
    UIntV Hand::rankCount(UIntA<HAND_LENGTH> list, Rank rank) {
        return list[static_cast<UIntV>(rank) - 2];
    }

    /**
     *
     */
    UIntA<HAND_LENGTH> Hand::toArray() const {
        UIntA<HAND_LENGTH> list;
        std::transform(m_cards.begin(), m_cards.end(), list.begin(),
                       [&](const CardPU& card) { return this->toInt(card); });
        return list;
    }

    /**
     *
     */
    UIntA<4> Hand::suits() {
        UIntA<4> handcount{};
        for (const CardPU& card : m_cards) {
            handcount[static_cast<UIntV>(card->suit()) - 1]++;
        }
        return handcount;
    }

    /**
     *
     */
    UIntA<13> Hand::ranks() {
        UIntA<13> rankcount{};
        for (const CardPU& card : m_cards) {
            rankcount[static_cast<std::size_t>(card->rank()) - 2]++;
        }
        return rankcount;
    }

    /**
     *
     */
    FloatA<4> Hand::suitHCP() {
        FloatA<4> suits{};
        for (const CardPU& card : m_cards) {
            suits[static_cast<std::size_t>(card->suit()) - 1] += this->rankScore(card->rank());
        }
        return suits;
    }

    /**
     *
     */
    float Hand::balanced() {
        float balanced = 0;
        UIntA<4> suits = this->suits();
        // Initialize variables to count suit distribution properties
        int voidCount = 0;       // Number of suits with 0 cards
        int singletonCount = 0;  // Number of suits with 1 card
        int doubletonCount = 0;  // Number of suits with 2 cards
        int maxSuitLength = 0;   // Maximum number of cards in any single suit

        // Iterate through the four suits to determine distribution properties
        for (int i = 0; i < 4; ++i) {
            if (suits[i] == 0) {
                voidCount++;
            } else if (suits[i] == 1) {
                singletonCount++;
            } else if (suits[i] == 2) {
                doubletonCount++;
            }
            // Keep track of the longest suit
            if (suits[i] > maxSuitLength) {
                maxSuitLength = suits[i];
            }
        }

        if (voidCount == 0 && singletonCount == 0 && doubletonCount <= 1 && maxSuitLength <= 5) {
            balanced = 1.0f;  // Hand is balanced
        } else {
            balanced = 0.0f;  // Hand is not balanced
        }
        return balanced;
    }

    /**
     *
     */
    float Hand::HCP() {
        float score{};
        for (const CardPU& card : m_cards) {
            score += this->rankScore(card->rank());
        }
        return score;
    }

    /**
     *
     */
    float Hand::rankScore(Rank rank) {
        float score{};
        score += rank == Rank::ACE ? ACE_POINTS : 0;
        score += rank == Rank::KING ? KING_POINTS : 0;
        score += rank == Rank::QUEEN ? QUEEN_POINTS : 0;
        score += rank == Rank::JACK ? JACK_POINTS : 0;
        score += rank == Rank::TEN ? TEN_POINTS : 0;
        return score;
    }
    /**
     *
     */
    float Hand::distribution() {
        float score{};
        UIntA<4> suits = this->suits();
        for (UIntV count : suits) {
            if (count <= 2) {
                score += 3 - count;
            }
        }
        return score;
    }

}  // namespace nobridge::engine
