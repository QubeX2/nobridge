#ifndef PBN_PBN_H
#define PBN_PBN_H

/**
 * (1) the identification section
 * (2) the auction section
 * (3) the play section
 * (4) supplemental section
 */

#include <memory>
#include <vector>

#include "parser.h"

namespace nobridge::pbn {

    GameL processFile(std::string const& path);

}  // namespace nobridge::pbn

#endif
