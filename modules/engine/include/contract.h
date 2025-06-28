#ifndef CONTRACT_H
#define CONTRACT_H

#include <cstdint>
#include <memory>

#include "bid.h"
#include "card.h"
#include "decl.h"
#include "player.h"
#include "types.h"

namespace nobridge::engine {

    class Contract : public Decl {
       public:
        void setDeclarer(Direction declarer) { m_declarer = declarer; }
        Direction declarer() const { return m_declarer; }

       private:
        Direction m_declarer = Direction::NONE;
    };

    inline std::ostream& operator<<(std::ostream& os, const ContractPU& c) {
        os << std::fixed << std::setprecision(2);
        os << "Contract: ";
        if (c->denomination() == Denomination::PASS) {
            os << "Pass" << "\n";

        } else {
            os << static_cast<int>(c->level()) << c->denomination();
            if (c->risk() == Risk::REDOUBLED) {
                os << "XX";
            } else if (c->risk() == Risk::DOUBLED) {
                os << "X";
            }
        }
        os << "\n";
        return os;
    }
}  // namespace nobridge::engine
#endif
