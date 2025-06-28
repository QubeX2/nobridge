#include "hand.h"

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
    float Hand::HCP() {
        float score{};
        for (const CardPU& card : m_cards) {
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
