#ifndef ENGINE_AUCTION_H
#define ENGINE_AUCTION_H

#include "types.h"

namespace nobridge::engine {

    class Auction {
       public:
        void setLevel(UIntV level) { m_level = level; }
        void setDenomination(Denomination denomination) { m_denomination = denomination; }
        void setRisk(Risk risk) { m_risk = risk; }

        UIntV level() const { return m_level; }
        Denomination denomination() const { return m_denomination; }
        Risk risk() const { return m_risk; }

       private:
        UIntV m_level{};
        Denomination m_denomination;
        Risk m_risk;
    };

}  // namespace nobridge::engine

#endif
