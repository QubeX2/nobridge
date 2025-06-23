#ifndef STORAGE_STORAGE_H
#define STORAGE_STORAGE_H

#include <cstddef>
#include <cstdint>

#include "gamerec.h"
#include "handrec.h"
#include "mika.h"

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

    template <typename T, std::size_t N>
    HandRec createHandRec(uint64_t gameid, const std::string hstr,
                          std::array<T, N> hvec, float length, float angle) {
        HandRec hr;
        hr.id = uniqueId();
        hr.gameid = gameid;
        mika::array::str2arr<100>(hr.str, hstr);
        hr.vect = hvec;
        hr.length = length;
        hr.angle = angle;
        return hr;
    }

    template <typename T, std::size_t N>
    inline std::ostream& operator<<(std::ostream& os, HandRec h) {
        os << std::fixed << std::setprecision(2);
        os << std::format("id: {}, gameid: {} \n(", h.id, h.gameid);
        mika::array::join(os, h.vect);
        os << std::format(") length: {}, angle: {}\n", h.length,
                          mika::math::toDegree(h.angle));
        return os;
    }

}  // namespace nobridge::storage

#endif
