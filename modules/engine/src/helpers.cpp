
#include <format>
#include <iostream>

#include "card.h"
#include "types.h"

namespace nobridge::engine {
    /**
     *
     */
    UIntV toIntFromCard(const CardP& card) {
        return (static_cast<UIntV>(card->suit()) - 1) * HAND_LENGTH + static_cast<UIntV>(card->rank()) - 1;
    }

    /**
     *
     */
    UIntA<HAND_LENGTH> toArrayFromCards(const CardL& cards) {
        UIntA<HAND_LENGTH> list;
        std::transform(cards.begin(), cards.end(), list.begin(),
                       [&](const CardP& card) { return toIntFromCard(card); });
        return list;
    }

    /**
     *
     */
    CardP toCardFromInt(const UIntV num) {
        if (num < 1 || num > 52) return nullptr;
        UIntV znum = num - 1;
        UIntV suit = (num / 13) + 1;
        UIntV rank = (num % 13) + 1;
        std::cout << std::format("Num: {}, Suit: {}, Rank: {}", num, suit, rank);
        CardP card = std::make_shared<Card>(static_cast<Suit>(suit), static_cast<Rank>(rank));
        return card;
    }

    /**
     *
     */
    UIntV rankCount(UIntA<HAND_LENGTH> list, Rank rank) { return list[static_cast<UIntV>(rank) - 2]; }

    /**
     *
     */
    UIntA<4> countSuits(const CardL& cards) {
        UIntA<4> handcount{};
        for (const CardP& card : cards) {
            handcount[static_cast<UIntV>(card->suit()) - 1]++;
        }
        return handcount;
    }

    /**
     *
     */
    UIntA<13> countRanks(const CardL& cards) {
        UIntA<13> rankcount{};
        for (const CardP& card : cards) {
            rankcount[static_cast<std::size_t>(card->rank()) - 2]++;
        }
        return rankcount;
    }

    /**
     *
     */
    float calculateHCP(const CardL& cards) {
        float score{};
        for (const CardP& card : cards) {
            score += card->rank() == Rank::ACE ? ACE_POINTS : 0;
            score += card->rank() == Rank::KING ? KING_POINTS : 0;
            score += card->rank() == Rank::QUEEN ? QUEEN_POINTS : 0;
            score += card->rank() == Rank::JACK ? JACK_POINTS : 0;
            score += card->rank() == Rank::TEN ? TEN_POINTS : 0;
        }
        return score;
    }

    /**
     *
     */
    float calculateDist(const CardL& cards) {
        float score{};
        UIntA<4> suits = countSuits(cards);
        for (UIntV count : suits) {
            if (count <= 2) {
                score += 3 - count;
            }
        }
        return score;
    }

}  // namespace nobridge::engine
