#ifndef STORAGE_STORAGE_H
#define STORAGE_STORAGE_H

#include <cstddef>
#include <cstdint>

#include "gamerec.h"
#include "handrec.h"
#include "mika.h"

/**
 * Bridge Records (.brs), Bridge Records Index (.bri)
 * games.brs, games.bri
 * hands.brs, hands.bri
 */
namespace nobridge::storage {

    uint64_t uniqueId();
    std::size_t write(std::string filename, const char* data, std::size_t size);
    std::size_t read(std::string filename, char* data, std::size_t size);

    template <typename T, std::size_t N>
    HandRec<T, N> createHandRec(uint64_t gameid, const std::string hstr,
                                std::array<T, N> hvec, float length,
                                float angle) {
        return HandRec{uniqueId(), gameid, hstr, hvec, length, angle};
    }

    GameRec createGameRec(uint64_t id, std::array<uint64_t, 4> hands);

    template <typename T, std::size_t N>
    inline std::ostream& operator<<(std::ostream& os, HandRec<T, N> h) {
        os << std::fixed << std::setprecision(2);
        os << std::format("id: {}, gameid: {} \n(", h.id, h.gameid);
        mika::array::join(os, h.vect);
        os << std::format(") length: {}, angle: {}\n", h.length,
                          mika::math::toDegree(h.angle));
        return os;
    }

}  // namespace nobridge::storage

#endif
