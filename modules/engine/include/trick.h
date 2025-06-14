#ifndef TRICK_H
#define TRICK_H

#include <memory>
#include <vector>

#include "card.h"
#include "player.h"

namespace nobridge::engine {

    class Trick {
       public:
        void add_card(std::shared_ptr<Card>& card);
        void add_card(std::shared_ptr<Card>& card,
                      std::shared_ptr<Player>& player);
        // get_winner??

       private:
        std::shared_ptr<Player> m_leader;
        std::vector<std::shared_ptr<Card>> m_cards;
    };

}  // namespace nobridge::engine

#endif
