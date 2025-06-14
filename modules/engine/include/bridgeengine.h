#ifndef BRIDGE_ENGINE_H
#define BRIDGE_ENGINE_H

#include "bidengine.h"
#include "deck.h"
#include "playengine.h"
#include "player.h"
#include "scoreengine.h"
#include <array>
#include <cstdint>
#include <memory>
namespace nobridge::engine {

class BridgeEngine {
  std::shared_ptr<Deck> m_deck;
  std::array<std::shared_ptr<Player>, 4> m_players;
  std::shared_ptr<BidEngine> m_bids;
  std::shared_ptr<PlayEngine> m_play;
  std::shared_ptr<ScoreEngine> m_scoring;

public:
  auto get_players() { return m_players; }
  void add_player(std::shared_ptr<Player>& player);
};

}

#endif
