#ifndef ENGINE_DECLARATION_H
#define ENGINE_DECLARATION_H

#include "types.h"

namespace nobridge::engine {

    class Decl {
       public:
        void setLevel(UIntV level) { m_level = level; }
        void setDenomination(Denomination denomination) { m_denomination = denomination; }
        void setRisk(Risk risk) { m_risk = risk; }

        UIntV level() const { return m_level; }
        Denomination denomination() const { return m_denomination; }
        Risk risk() const { return m_risk; }

        virtual ~Decl() = default;

       private:
        UIntV m_level{};
        Denomination m_denomination = Denomination::PASS;
        Risk m_risk = Risk::VOID;
    };

}  // namespace nobridge::engine

#endif
