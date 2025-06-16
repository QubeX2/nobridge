add_executable(nobridge
  main.cpp
)

target_link_libraries(nobridge
  PRIVATE 
  mkrl
  engine
  pbn
  storage
)

set_target_properties(nobridge PROPERTIES FOLDER "apps/CLI")


