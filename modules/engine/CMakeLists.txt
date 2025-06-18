add_library(engine STATIC
  src/bid.cpp
  src/bidengine.cpp
  src/bridgeengine.cpp
  src/card.cpp
  src/contract.cpp
  src/deck.cpp
  src/playengine.cpp
  src/player.cpp
  src/scoreengine.cpp
  src/trick.cpp
  src/engine.cpp
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(engine PUBLIC cxx_std_23)



