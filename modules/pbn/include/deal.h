#ifndef PBN_DEAL_H
#define PBN_DEAL_H

#include <array>
#include <string>
#include <vector>
namespace nobridge::pbn {

    struct Deal {
        std::array<std::string, 4> hands;
        std::string dealer;
        std::string vulnerable;
    };

}  // namespace nobridge::pbn

#endif
