#include "storage.h"

#include <sys/types.h>

#include <array>
#include <cstdint>
#include <fstream>
#include <ios>
#include <random>

#include "gamerec.h"
#include "handrec.h"
#include "types.h"
#include "vmath.h"

namespace nobridge::storage {

    /**
     *
     */
    HandRec createHandRec(const UIntID gameid, UIntA<HAND_LENGTH> cards,
                          FloatA<vmath::VECT_HAND_SIZE> hvec, float length, float angle) {
        HandRec hr;
        hr.id = uniqueId();
        hr.gameid = gameid;
        hr.vect = hvec;
        hr.cards = cards;
        hr.length = length;
        hr.angle = angle;
        return hr;
    }

    /**
     *
     */
    void save(const GameRec& record) {
        write(kRecordsPath + kGameRecords, reinterpret_cast<const char*>(&record), sizeof(GameRec));
    }

    /**
     *
     */
    void save(const HandRec& record) {
        write(kRecordsPath + kHandRecords, reinterpret_cast<const char*>(&record), sizeof(HandRec));
    }

    /**
     *
     */
    uint64_t uniqueId() {
        uint64_t time_since_epoch =
            std::chrono::high_resolution_clock::now().time_since_epoch().count();
        static std::mt19937_64 generator(std::random_device{}());
        return time_since_epoch ^ generator();
    }

    /**
     *
     */
    std::size_t write(std::string filename, const char* data, std::size_t size) {
        std::ofstream output(filename, std::ios::binary);
        if (!output) return -1;
        output.write(data, size);
        output.close();
        if (!output.good()) return -1;
        return size;
    }  // namespace nobridge::storage

    /**
     *
     */
    std::size_t read(std::string filename, char* data, std::size_t size) {
        std::ifstream input(filename);
        if (!input) return -1;
        input.read(data, size);
        input.close();
        if (!input.good()) return -1;
        return size;
    }

}  // namespace nobridge::storage
