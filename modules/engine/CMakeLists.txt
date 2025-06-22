add_library(engine STATIC
  src/bid.cpp
  src/game.cpp
  src/card.cpp
  src/hand.cpp
  src/contract.cpp
  src/deck.cpp
  src/player.cpp
  src/score.cpp
  src/trick.cpp
  src/engine.cpp
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(engine PUBLIC cxx_std_23)



