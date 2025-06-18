add_executable(nobridge
  main.cpp
)

target_link_libraries(nobridge
  PRIVATE 
  mika
  engine
  pbn
  storage
)

set_target_properties(nobridge PROPERTIES FOLDER "apps/CLI")


