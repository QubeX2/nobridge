#ifndef STORAGE_STORAGE_H
#define STORAGE_STORAGE_H

#include <cstddef>
#include <cstdint>

#include "gamerec.h"
#include "handrec.h"
#include "mika.h"
#include "types.h"
#include "vmath.h"

/**
 * Bridge Records (.brs), Bridge Records Index (.bri)
 *
 * games.brs  id
 * hands.brs  id|gameid|length|angle|vect|str
 * bids.brs   id|gameid|type|bid|level
 * plays.brs   id|gameid
 */
namespace nobridge::storage {

    const std::string kRecordsPath = "./";
    const std::string kGameRecords = "games.brs";
    const std::string kHandRecords = "hands.brs";
    const std::string kBidRecords = "bids.brs";
    const std::string kPlayRecords = "plays.brs";

    uint64_t uniqueId();

    void save(const GameRec& record);
    void save(const HandRec& record);

    std::size_t write(std::string filename, const char* data, std::size_t size);
    std::size_t read(std::string filename, char* data, std::size_t size);

    HandRec createHandRec(const UIntID gameid, UIntA<HAND_LENGTH> cards,
                          FloatA<vmath::VECT_HAND_SIZE> hvec, float length);

    template <typename T, std::size_t N>
    inline std::ostream& operator<<(std::ostream& os, HandRec h) {
        os << std::fixed << std::setprecision(2);
        os << std::format("id: {}, gameid: {} \n(", h.id, h.gameid);
        mika::array::join(os, h.vect);
        os << std::format(") length: {}, angle: {}\n", h.length, mika::math::toDegree(h.angle));
        return os;
    }

}  // namespace nobridge::storage

#endif
