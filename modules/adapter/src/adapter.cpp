

#include "adapter.h"

#include <memory>
#include <unordered_set>

#include "card.h"
#include "deck.h"
#include "game.h"
#include "mika.h"
#include "parser.h"
#include "player.h"
#include "types.h"

namespace nobridge::adapter {

    /**
     *
     */
    engine::GamePU toGame(const nobridge::pbn::TagM& tags) {
        const static StringA<4> directions{"North", "East", "South", "West"};
        const static std::unordered_set<std::string> check_vuln{"All", "Both"};

        engine::GamePU game = std::make_unique<engine::Game>();
        /////////////////////////////////
        // Player
        std::string sdeal = pbn::getTagValue(tags, "Deal");
        std::string sdealer = pbn::getTagValue(tags, "Dealer");
        std::string svuln = pbn::getTagValue(tags, "Vulnerable");

        // -- Dealer
        game->setDealer(engine::DIRECTION_M.at(sdealer.front()));

        // -- Vulnerable
        engine::Vulnerable vuln = engine::Vulnerable::NONE;
        if (check_vuln.contains(svuln)) {
            vuln = engine::Vulnerable::BOTH;
        } else if (svuln == "NS") {
            vuln = engine::Vulnerable::NS;
        } else if (svuln == "EW") {
            vuln = engine::Vulnerable::EW;
        }
        game->setVulnerable(vuln);

        // -- Player, Hand
        engine::DealL deal = toDeal(sdeal);
        if (deal.size() == 4) {
            for (std::size_t i = 0; i < directions.size(); ++i) {
                std::string dir = directions[i];
                if (const pbn::Tag* tag = pbn::getTag(tags, dir)) {
                    // Vulnerable
                    std::string name = pbn::getTagValue(tags, dir);
                    engine::PlayerPU player = std::make_unique<engine::Player>(
                        name, engine::PlayerType::HUMAN,
                        std::make_unique<engine::Hand>(std::move(deal[i])));
                    game->addPlayer(static_cast<engine::Direction>(i + 1), std::move(player));
                }
            }
        }

        /////////////////////////////////
        // Play
        const pbn::Tag* tag = pbn::getTag(tags, "Play");
        engine::PlayPU play = std::make_unique<engine::Play>();
        play->setDirection(engine::DIRECTION_M.at(tag->value.front()));
        for (auto line : tag->lines) {
            StringL scards = mika::string::split(line, ' ');
            engine::TrickA trick;
            for (std::size_t i = 0; i < scards.size(); i++) {
                engine::CardPU card = toCard(scards[i]);
                if (card != nullptr) {
                    trick[i] = std::move(card);
                }
            }
            play->addTrick(std::move(trick));
        }
        game->addPlay(std::move(play));

        /////////////////////////////////
        // Contract
        engine::ContractPU contract = std::make_unique<engine::Contract>();
        const pbn::Tag* tagDecl = pbn::getTag(tags, "Declarer");
        const pbn::Tag* tagCont = pbn::getTag(tags, "Contract");
        if (tagDecl->value.length() > 0) {
            contract->setDeclarer(engine::DIRECTION_M.at(tagDecl->value.front()));
        }
        if (tagCont->value != "Pass") {
            contract->setLevel(std::stoi(tagCont->value.substr(0, 1)));
            if (tagCont->value.ends_with("XX")) {
                contract->setRisk(engine::Risk::REDOUBLED);
            } else if (tagCont->value.ends_with("X")) {
                contract->setRisk(engine::Risk::DOUBLED);
            }

            if (tagCont->value.contains("NT")) {
                contract->setDenomination(engine::Denomination::NOTRUMP);
            } else {
                contract->setDenomination(
                    engine::DENOMINATION_M.at(tagCont->value.substr(1, 1).front()));
            }
        }
        /////////////////////////////////
        // Bids

        game->setContract(std::move(contract));

        /////////////////////////////////
        // Game
        return std::move(game);
    }

    /**
     *
     */
    engine::CardPU toCard(const std::string& string) {
        if (string.length() == 2) {
            std::string suit = string.substr(0, 1);
            std::string rank = string.substr(1, 1);
            if (std::string("SHDC").contains(suit)) {
                engine::CardPU card = std::make_unique<engine::Card>(engine::SUIT_M.at(suit[0]),
                                                                     engine::RANK_M.at(rank[0]));
                return std::move(card);
            }
        }
        return nullptr;
    }

    /**
     *
     */
    std::string toHandstr(const engine::CardL& cards) {
        StringA<4> suits;
        for (const engine::CardPU& card : cards) {
            suits[static_cast<std::size_t>(card->suit()) - 1] += card->rankText();
        }
        return mika::array::join(suits, ".");
    }

    /**
     *
     */
    engine::DealL toDeal(const std::string& dealstr) {
        engine::DealL deals;

        StringL hands = mika::string::split(dealstr.contains(':') ? dealstr.substr(2) : "", ' ');
        for (auto hand : hands) {
            engine::CardL deal;
            if (hand != "-") {
                StringL suits = mika::string::split(hand, '.');
                for (auto it = suits.begin(); it != suits.end(); ++it) {
                    std::size_t index2 = it - suits.begin();
                    for (char c : (*it)) {
                        deal.push_back(std::make_unique<engine::Card>(engine::SUIT_A[index2],
                                                                      engine::RANK_M.at(c)));
                    }
                }
            }
            deals.push_back(std::move(deal));
        }
        return deals;
    }  // namespace pbn
}  // namespace nobridge::adapter
