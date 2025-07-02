
#include <cstddef>
#include <filesystem>
#include <ios>
#include <iostream>
#include <span>
#include <vector>

#include "adapter.h"
#include "contract.h"
#include "game.h"
#include "pbn.h"
#include "types.h"
#include "vmath.h"

using namespace nobridge;

void import_pbn(std::string pbn_file) {
    if (std::filesystem::exists(pbn_file)) {
        pbn::TagML tagslist = pbn::processFile(pbn_file);
        for (const pbn::TagM& tags : tagslist) {
            engine::GamePU game = adapter::toGame(tags);
            UIntV dir = static_cast<UIntV>(game->auction()->direction());
            UIntV ix = dir - 1;
            vmath::ContractVect cur_contract;
            std::vector<vmath::ContractVect> player_contracts;
            vmath::ContractVect bdr_contract;
            vmath::ContractVect ptn_contract;
            std::cout << game->auction() << "\n";
            for (const engine::BidA& bid : game->auction()->bids()) {
                for (UIntV i = 0; i < 4; i++) {
                    if (bid[i] != nullptr) {
                        bdr_contract = vmath::toContract(bid[i]);
                        if (player_contracts.size() >= 2) {
                            // ptn_contract = player_contracts[0];
                        }
                        player_contracts.push_back(bdr_contract);
                        if (bid[i]->denomination() != engine::Denomination::PASS) {
                            // std::cout << "bidder: " << bdr_contract << "\n";
                            const engine::HandPU& hand =
                                game->getPlayer(static_cast<engine::Direction>(ix))->hand();
                            vmath::HandVect hv = vmath::toVector(hand);
                            vmath::AuctionVect auction =
                                vmath::toAuction(hv, bdr_contract, ptn_contract, cur_contract);
                            // std::cout << auction << "\n";
                            cur_contract = bdr_contract;
                        }
                    }
                    ix = (ix + 1) % 4;
                }
            }
            break;
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
