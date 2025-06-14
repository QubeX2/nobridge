#ifndef PBN_DEAL_H
#define PBN_DEAL_H

#include <array>
#include <string>
#include <vector>
namespace nobridge::pbn {

    class Deal {
       public:
       private:
        std::array<std::string, 4> m_hands;
        std::string m_dealer;
        std::string m_vulnerable;
    };

}  // namespace nobridge::pbn

#endif
