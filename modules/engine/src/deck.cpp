#include "deck.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <print>
#include <random>
#include <utility>

#include "card.h"

namespace nobridge::engine {

    Deck::Deck() {
        size_t index = 0;
        for (uint8_t s = 1; s <= 4; s++) {
            for (uint8_t r = 2; r <= 14; r++) {
                m_cards.push_back(std::make_shared<Card>(static_cast<Suit>(s),
                                                         static_cast<Rank>(r)));
            }
        }
        this->shuffle();
    }

    void Deck::shuffle() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 51);
        for (int i = 0; i < 256; i++) {
            size_t a = dist(gen);
            size_t b = dist(gen);
            if (a != b) {
                std::swap(m_cards[a], m_cards[b]);
            }
        }
    }

    CardPtr Deck::at(size_t index) {
        if (index < m_cards.size()) {
            return m_cards.at(index);
        }
        return nullptr;
    }

}  // namespace nobridge::engine
