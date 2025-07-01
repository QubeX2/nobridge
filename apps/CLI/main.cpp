
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <span>

#include "adapter.h"
#include "game.h"
#include "pbn.h"
#include "types.h"

using namespace nobridge;

void import_pbn(std::string pbn_file) {
    if (std::filesystem::exists(pbn_file)) {
        pbn::TagML tagslist = pbn::processFile(pbn_file);
        for (const pbn::TagM& tags : tagslist) {
            engine::GamePU game = adapter::toGame(tags);
            std::cout << game;
        }
    }
}

int main(int argc, char** argv) {
    auto args = std::span(argv, static_cast<std::size_t>(argc));
    for (std::size_t i = 0; i < args.size(); i++) {
        if (std::string(args[i]) == "-f" && (i + 1) < args.size()) {
            std::string pbn_file = std::string(args[i + 1]);
            import_pbn(pbn_file);
        }
    }
    return 0;
}
