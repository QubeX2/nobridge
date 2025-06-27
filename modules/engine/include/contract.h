#ifndef CONTRACT_H
#define CONTRACT_H

#include <cstdint>
#include <memory>

#include "bid.h"
#include "card.h"
#include "player.h"
#include "types.h"

namespace nobridge::engine {

    class Contract {
       public:
        void setLevel(UIntV level) { m_level = level; }
        void setDenomination(Denomination denomination) { m_denomination = denomination; }
        void setDeclarer(Direction declarer) { m_declarer = declarer; }
        void setRisk(Risk risk) { m_risk = risk; }

        UIntV level() const { return m_level; }
        Denomination denomination() const { return m_denomination; }
        Risk risk() const { return m_risk; }
        Direction declarer() const { return m_declarer; }

       private:
        UIntV m_level{};
        Denomination m_denomination = Denomination::PASS;
        Risk m_risk = Risk::VOID;
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
        return os;
    }
}  // namespace nobridge::engine
#endif
