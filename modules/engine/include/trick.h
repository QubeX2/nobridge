#ifndef TRICK_H
#define TRICK_H

#include <memory>
#include <vector>

#include "card.h"
#include "player.h"

namespace nobridge::engine {

    class Trick {
       public:
        void addCard(CardPtr& card);
        void addCard(CardPtr& card, PlayerPtr& player);
        // get_winner??

       private:
        PlayerPtr m_leader;
        CardList m_cards;
    };

}  // namespace nobridge::engine

#endif
